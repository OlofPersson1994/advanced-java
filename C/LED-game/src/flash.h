#ifndef FLASH_H_
#define FLASH_H_

#include <stdio.h>

void waitMs(unsigned int milllis);

void flash(uint8_t pinA, uint8_t pinB, int ms);

void restart(unsigned int restartTime);

#endif