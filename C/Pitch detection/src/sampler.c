#include <stdio.h>
#include <driver/timer.h>
#include "esp_timer.h"
#include <driver/adc.h>
#include "sampler.h"
#include <esp_task_wdt.h>

volatile unsigned int val;
int averageVoltage = 1250;
volatile int oldValue;
volatile int newValue = 0;
static int crossingCounter = 0;
float returnValue;
volatile float startTime = 0;
volatile float stopTime = 0;

//gets the time in seconds

int millis()
{
    int time = esp_timer_get_time() / 1000;
    return time;
}
// this is what actuall happens in the timer, and starts it. We check how many crossings that we make in our soundwave. 

void timerISR()
{

    uint32_t is_t0 = TIMERG0.int_st_timers.t0;

    if (is_t0)
    {
        oldValue = newValue;

        TIMERG0.int_clr_timers.t0 = 1;

        val = adc1_get_raw(ADC1_GPIO32_CHANNEL);

        newValue = val;

        if (newValue > averageVoltage && oldValue < averageVoltage)
        {
            crossingCounter++;
        }

        if (newValue < averageVoltage && oldValue > averageVoltage)
        {
            crossingCounter++;
        }

        TIMERG0.hw_timer[0].config.alarm_en = TIMER_ALARM_EN;
    }
}
// we are setting up our timer. We are deviding with freq (freq = 40000) This is becuase 80 MHz / 40000 = 2000 Hz.
// we also setup and starts our adc
void startSampling(int freq)
{
    timer_config_t timerConfig;

    timerConfig.auto_reload = TIMER_AUTORELOAD_EN;

    timerConfig.alarm_en = TIMER_ALARM_EN;

    timerConfig.counter_en = TIMER_PAUSE;

    timerConfig.counter_dir = TIMER_COUNT_UP;

    timerConfig.divider = freq;

    timerConfig.intr_type = TIMER_INTR_LEVEL;

    timer_init(TIMER_GROUP_0, TIMER_0, &timerConfig);

    timer_set_counter_value(TIMER_GROUP_0, TIMER_GROUP_0, 0x00000000ULL);

    timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, 1); // 2000 / 1 = 2000 Hz 

    timer_enable_intr(TIMER_GROUP_0, TIMER_0);

    timer_isr_register(TIMER_GROUP_0, TIMER_0, timerISR, NULL, 0, NULL);

    timer_start(TIMER_GROUP_0, TIMER_0);

    adc_power_on();

    adc_gpio_init(ADC_UNIT_1, ADC1_GPIO32_CHANNEL);

    adc1_config_width(ADC_WIDTH_BIT_12);

    adc1_config_channel_atten(ADC1_GPIO32_CHANNEL, ADC_ATTEN_DB_11);

    startTime = esp_timer_get_time();

}
// we stops the timer.
void stopSampling()
{
    adc_power_off();

    stopTime = esp_timer_get_time();

    timer_pause(TIMER_GROUP_0, TIMER_0);

}
//we are creating the average soundwave of our sound.
float getFrequency()
{
    float samplingTime = ((stopTime - startTime) / 1000000);

    returnValue = (crossingCounter / (samplingTime * 2));

    crossingCounter = 0;

    stopTime = 0;
    startTime = 0;

    return returnValue;
}
