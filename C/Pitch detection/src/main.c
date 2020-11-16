#include <stdio.h>
#include "driver/dac.h"
#include <esp_task_wdt.h>
#include "driver/adc.h"
#include "soc/syscon_reg.h"
#include "soundgen.h"
#include "sampler.h"
#include "leds.h"
#include "flash.h"
#include "random.h"

float playerFreq;
int radomFreq;
int actualFreq;

/*Makes the value allways <= 0 */
float absVal(float a)
{
    if(a < 0)
    {
        return -a;
    }

    else
    {
        return a;
    }
}

void app_main() {

    initPins();
    
    
    while(1){

        printf("\n \nStart Game! \n");

       startFlash(300, 2);
        // gets a random number between 200 and 1000;
        radomFreq = getRandomFreq(200, 1000); 
        // starts a sound with a frequence that is the same as the random number
        actualFreq = startSound(radomFreq); 

        vTaskDelay(pdMS_TO_TICKS(1000)); 
        // stops playing the sound
        stopSound();
        // start listening on your own sound.
        startSampling(4000);

        vTaskDelay(pdMS_TO_TICKS(2000));
        // stop listining on you own sound
        stopSampling();
        //gets a average of your sound and create a sound out of that
        playerFreq = getFrequency();

        printf("Players sound: %f, Actual sound: %d\n", playerFreq, actualFreq); 
        // if you are withing the range of 50 Hz from the playingsound you will win
        if (absVal(playerFreq - (float)actualFreq) < 50 )
        {
            printf("Player win \n");
            winFlash(1000);
        }
        else
        {
            printf("Player lose! \n");
            lostFlash(1000);
        }

    }
    
}

