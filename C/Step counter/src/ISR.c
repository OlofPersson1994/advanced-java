//Authors Olof Persson Karl Andersson
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <math.h>
#include <driver/gpio.h>
#include "circular_buffer/circular_buffer.h"
#include "ISR.h"
#include <esp_int_wdt.h>
#include "accelerometer.h"

struct circularBuffer bufferCircular;
//minimum change from accelerometer that counts as a step
#define MIN_SD 1000
//how often we run the algorithm
#define ALGO_PERIOD 6000
//A average runner takes 3 steps per seconds doubled it according to Harry (Nyquist)
#define SAMPLING_PERIOD 60
//minimum time between steps
#define MIN_INTRA_STEP_TIME 300
//from testing we got this K value
#define K 1.3
//step goal
#define step_goal 10
//pin for leds
#define led_Pin 27
int steps;
int led_status = 0;
SemaphoreHandle_t xSemaphore;

//gets the values from the accelerometer
void readValueFromAccelerometer(void *arg)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        getValuesXYZ();
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(SAMPLING_PERIOD));
    }
}

//Calculating the steps
void walkingAlgorithm(void *arg)
{
    int32_t sd;
    int32_t mean;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1)
    {

        uint32_t numberBufferValues = containsNumberOfValues(&bufferCircular);
        uint32_t sum = addAllValuesInBuffer(&bufferCircular);

        if (numberBufferValues > 0)
        {

            mean = sum / numberBufferValues;
            uint32_t tempval1 = addAllValuesInBufferMinusValue(&bufferCircular, mean);
            sd = (uint32_t)sqrt((double)(tempval1 / numberBufferValues));

            if (sd < MIN_SD)
            {
                sd = MIN_SD;
            }

            int lastStepTS = 0;

            for (int i = 0; i < containsNumberOfValues(&bufferCircular); i++)
            {

                if ((double)removeHead(&bufferCircular) > ((K * sd) + mean))
                {
                    if ((i - lastStepTS) * (SAMPLING_PERIOD) > MIN_INTRA_STEP_TIME)
                    {
                        steps++;
                        lastStepTS = i;
                    }
                }
            }

            printf("Steps: %d\n", steps);
        }

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(ALGO_PERIOD));
    }
}
//samaphore for the button.
void button_isr_handler(void *arg)
{
    xSemaphoreGiveFromISR(xSemaphore, NULL);
}

//hadles the turning on and off of the led based on if the step goal is reached.
void led_task(void *arg)
{
    while (1)
    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            if (steps > step_goal)
            {
                led_status = !led_status;
                gpio_set_level(led_Pin, led_status);
            }
        }
    }
}