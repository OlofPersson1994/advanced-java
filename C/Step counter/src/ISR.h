//Authors Olof Persson Karl Andersson
#ifndef ISR_H_
#define ISR_H_

void readValueFromAccelerometer(void *arg);

void walkingAlgorithm(void *arg);

void button_isr_handler(void *arg);

void led_task(void *arg);

#endif 