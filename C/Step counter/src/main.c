//Authors Olof Persson Karl Andersson
#include <driver/i2c.h>
#include <stdio.h>
#include <math.h>
#include <esp_pm.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <driver/gpio.h>
#include <esp_int_wdt.h>
#include "circular_buffer/circular_buffer.h"
#include "ISR.h"
#include "accelerometer.h"
#include "pins.h"
/*
Example program that reads data from MPU6050
Connections:
Vcc -> 3.3V
GND -> GND
SCL -> 32
SDA -> 33
AD0 -> GND

Test how accurate the step counter is:
Steps taken 65 over 5 tests different number of steps in each test 
Steps counted by the tracker 62
accuracy percentage of detected steps over actual steps is 62/65 = 0,954 so a 95,4% accuracy
*/

//buffer size for storage of values from accelerometer
#define BUFFER_SIZE 1000

//priority of the different tasks
#define SAMPLING_PRIORITY 8
#define ALGO_PRIORITY 9
#define LED_PRIORITY 10

struct circularBuffer bufferCircular;
SemaphoreHandle_t xSemaphore = NULL;

void sleepMode();

void app_main()
{
    int *buffer_data = (int *)malloc(BUFFER_SIZE * sizeof(uint32_t));
    initCircularBuffer(&bufferCircular, buffer_data, BUFFER_SIZE);
    
    sleepMode();

    initI2C(33, 32);
    initledButton();

    xSemaphore = xSemaphoreCreateBinary();

    xTaskCreate(readValueFromAccelerometer, "accelleration_Change", 2048, NULL, SAMPLING_PRIORITY, NULL);
    xTaskCreate(walkingAlgorithm, "check_step", 2048, NULL, ALGO_PRIORITY, NULL);
    xTaskCreate(led_task, "button_goal_reached", 2048, NULL, LED_PRIORITY, NULL);


}
//config for power saving/sleepmode
void sleepMode()
{
    esp_pm_config_esp32_t conf_sleep_light_mode = {
        .light_sleep_enable = true,
        .max_freq_mhz = 80,
        .min_freq_mhz = 13};
    esp_err_t error = esp_pm_configure(&conf_sleep_light_mode);
    ESP_ERROR_CHECK(error);
}
