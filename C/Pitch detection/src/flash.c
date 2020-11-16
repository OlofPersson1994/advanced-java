#include "flash.h"
#include "leds.h"
#include <esp_task_wdt.h>

/* waitMs helps us with delay in the game and to deal with the watchdog, code made to labb1 */

void waitMs(unsigned int milllis)
{

    TickType_t delay = milllis / portTICK_PERIOD_MS;
    vTaskDelay(delay);
}

/* The lights flashes in a pattern when the game starts/restarts */
void startFlash(int ms, int laps)
{

    for (int i = 0; i <= laps; i++)
    {

  
        setLEDA(1);
        setLEDB(1);
        waitMs(ms);
        setLEDA(0);
        setLEDB(0);
        waitMs(ms);
        setLEDA(1);
        setLEDB(1);
        waitMs(ms);
        setLEDA(0);
        setLEDB(0);
        waitMs(ms);
        setLEDA(1);
        setLEDB(1);
        setLEDA(0);
        setLEDB(0);
    }
}

/* When the game restarts. Puts both leds to 0 and wait for a time. */

void restart(unsigned int restartTime)
{

    setLEDA(0);
    setLEDB(0);

    waitMs(restartTime);
}

/*If you lose the lights flashes */
void lostFlash(int ms)
{       
        setLEDB(0);
        setLEDA(1);
        waitMs(ms);
        setLEDA(0);
        waitMs(ms);
        setLEDA(1);
        waitMs(ms);
        setLEDA(0);
        waitMs(ms);
}
/*If you win the lights flashes */
void winFlash(int ms)
{       
        setLEDA(0);
        setLEDB(1);
        waitMs(ms);
        setLEDB(0);
        waitMs(ms);
        setLEDB(1);
        waitMs(ms);
        setLEDB(0);
        waitMs(ms);
}