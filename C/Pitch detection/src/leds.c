#include "leds.h"
#include "driver/gpio.h"
#include "driver/pcnt.h"

#define PIN1 12
#define PIN2 14

/* Makes pin 12,14 to GPIOs then I tell  pin 12 and 14 to be outputs. */

void initPins(){

    gpio_pad_select_gpio(PIN1);
    gpio_pad_select_gpio(PIN2);


    gpio_set_direction(PIN1, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN2, GPIO_MODE_OUTPUT);

}

/* The function gets a 1 or a 0. If it gets a 1 = start light. 0 = Turn off light. Same for setLEDB  */

void setLEDA(uint8_t level){

    if(level){

            gpio_set_level(PIN1,1);
    }
    else
    {
        gpio_set_level(PIN1,0);
    }
    
}

void setLEDB(uint8_t level){

    if(level){


        gpio_set_level(PIN2, 1);
    }
    else
    {
        
        gpio_set_level(PIN2, 0);
    }
    
}