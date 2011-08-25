#ifndef __GPIO_H__
#define __GPIO_H__

#include "LPC11xx.h"

#define HIGH 1
#define LOW 0

void pin_mode(uint8_t pin, uint8_t mode);
void digital_write(uint8_t pin, uint8_t bitVal);
void delayms(uint32_t millis);
void delayus(uint32_t micros);

#endif
