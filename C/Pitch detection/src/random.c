#include "random.h"
#include "esp_system.h"

/* getRandommssecs gets a value betweeen 0 and uint32_max but we change it so r between 0 and 1. After that we use our input
    to get a time between out min and max input. */

int getRandomFreq(int min, int max){

    float r = esp_random();

    r = r / UINT32_MAX;

    r = min + r*(max - min);

    return r;
}

