#include "pins.h"
#include "driver/gpio.h"

#define PIN1 12
#define PIN2 14
#define BT1 27
#define BT2 26

/* Makes pin 12,14,27 and 26 to GPIOs then I tell  pin 12 and 14 to be outputs and 27 and 26 to inputs.
    I make pin 27 and 26 to pullups */

void initPins(){

    gpio_pad_select_gpio(PIN1);
    gpio_pad_select_gpio(PIN2);
    gpio_pad_select_gpio(BT1);
    gpio_pad_select_gpio(BT2);

    gpio_set_direction(PIN1, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN2, GPIO_MODE_OUTPUT);
    gpio_set_direction(BT1, GPIO_MODE_INPUT);
    gpio_set_direction(BT2, GPIO_MODE_INPUT);

    gpio_pullup_en(BT1);
    gpio_pullup_en(BT2);

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

uint8_t isButtonAPressed(){
    
   return !gpio_get_level(BT1);
}

uint8_t isButtonBPressed(){

   return !gpio_get_level(BT2);
}