#ifndef __HARDWARE_GPIO_H_
#define __HARDWARE_GPIO_H_

#include "LPC11xx.h"

#define HIGH 1
#define LOW 0

#define IN 0
#define OUT 1

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin,uint8_t bitVal);
uint8_t digitalRead(uint8_t pinl);
void delayms(uint32_t millis);
void delayus(uint32_t micros);

#endif
