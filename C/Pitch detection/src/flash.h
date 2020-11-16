#ifndef FLASH_H_
#define FLASH_H_


void waitMs(unsigned int milllis);

void startFlash(int ms, int laps);

void lostFlash(int ms);

void winFlash(int ms);

void restart(unsigned int restartTime);

#endif