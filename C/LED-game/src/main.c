#include "driver/gpio.h"
#include <esp32/rom/ets_sys.h>
#include "pins.h"
#include "random.h"
#include "flash.h"
#include "esp_timer.h"

#define wonPlayer1 1
#define lostPlayer1 0
#define wonPlayer2 1
#define lostPlayer2 0
#define blinkingTime 500

uint8_t winner;

    /* waitingTime is a delay but the program is still checking is a button is pressed during delay */

    void waitingTime(int randomTime){

        unsigned int startMs = esp_timer_get_time() / 1000;
        
        while ((esp_timer_get_time()/1000) - startMs < randomTime){

        /* If a button is pressed during the wating time, the other player will win */

        if(isButtonAPressed()){

            winner = 2;

            break;
        }

        if(isButtonBPressed()){

            winner = 1;

            break;
        }

        }
    }

void app_main() {

    /* You find initPins in pins.c */

    initPins();


    while (1){

        /* My main loop that starts with putting reset the winner from last game = 0. And and start/ turn off the lights */ 

        winner = 0;
    
    /* You find setLEDA / setLEDB in pins.  */

        setLEDA(1);
        setLEDB(1);

    /* You find waitMs in flash.c. inpust is is in ms */
        waitMs(3000);

        setLEDA(0);
        setLEDB(0);

    /* You find getRandomnssecs in random.c. Input is in ms */

        int randomTime = getRandommssecs(3000, 5000);

        waitingTime(randomTime);
       
        setLEDA(1);
        setLEDB(1);

    /* When we are wainting for someone to press/win we will be in this loop */ 

        while(!winner){

            if(isButtonAPressed()){

                winner = 1;
            }
            if (isButtonBPressed()){

                winner = 2;
            }
        }

        if(winner == 1){

            /*You find flash in flash.c */

            flash(wonPlayer1,lostPlayer2, blinkingTime);
            
        }
        if(winner == 2){

            flash(lostPlayer1,wonPlayer2,blinkingTime);
        }
        /* You find restart in flash.c */

        restart(5000);
    }

}