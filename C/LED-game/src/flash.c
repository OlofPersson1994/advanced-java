#include "flash.h"
#include "pins.h"
#include <esp_task_wdt.h>

/* waitMs helps us with delay in the game and to deal with the watchdog */ 

void waitMs(unsigned int milllis){

    TickType_t delay = milllis /portTICK_PERIOD_MS;
    vTaskDelay(delay);
}


/* Two loops in this function, one if player1 wins and one for player2.  */

void flash(uint8_t pinA, uint8_t pinB, int ms){

    if(pinA == 1 && pinB == 0){

            setLEDB(0);
            setLEDA(1);
            waitMs(ms);
            setLEDA(0);
            waitMs(ms);
            setLEDA(1);
            waitMs(ms);
            setLEDA(0);
            waitMs(ms);
            setLEDA(1);
            waitMs(ms);
            setLEDA(0);


    }

    if(pinA == 0 && pinB == 1){


            setLEDA(0);
            setLEDB(1);
            waitMs(ms);
            setLEDB(0);
            waitMs(ms);
            setLEDB(1);
            waitMs(ms);
            setLEDB(0);
            waitMs(ms);
            setLEDB(1);
            waitMs(ms);
            setLEDB(0);

    }
}

/* When the game restarts. Puts both leds to 0 and wait for a time. */

void restart(unsigned int restartTime){

    setLEDA(0);
    setLEDB(0);

    waitMs(restartTime);
}

