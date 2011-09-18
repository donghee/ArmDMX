#ifndef __HARDWARE_UTILS_H
#define __HARDWARE_UTILS_H

#include "LPC11xx.h"
#include "gpio.h"
#include "timer32.h"


#define HIGH 1
#define LOW 0

#define ON 1
#define OFF 0

#define IN 0
#define OUT 1

void pinMode(uint8_t pin, uint8_t mode);
void portPinMode(uint8_t port, uint8_t pin, uint8_t mode);
void digitalPortPinWrite(uint8_t port, uint8_t pin, uint8_t bitVal);
void digitalWrite(uint8_t pin,uint8_t bitVal);
uint8_t digitalPortPinRead(uint8_t port, uint8_t pin);
uint8_t digitalRead(uint8_t pinl);
void delayms(uint32_t millis);
void delayus(uint32_t micros);

#endif
