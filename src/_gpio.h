#ifndef ___GPIO_H
#define ___GPIO_H

#include "LPC11xx.h"
#include "gpio.h"

#define HIGH 1
#define LOW 0

#define PORT 3

void pin_mode(uint8_t pin, uint8_t mode);
void digital_write(uint8_t pin,uint8_t bitVal);
void delayms(uint32_t millis);
void delayus(uint32_t micros);

#endif
