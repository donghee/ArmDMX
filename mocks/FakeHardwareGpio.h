#ifndef __FAKE_HARDWARE_GPIO_H__
#define __FAKE_HARDWARE_GPIO_H__

#include "LPC11xx.h"
#include "HardwareGpio.h"

void Fake_pinMode(uint8_t pin, uint8_t mode);
void Fake_digitalWrite(uint8_t pin, uint8_t bitVal);
uint8_t Fake_digitalRead(uint8_t pin);
void Fake_delayms(uint32_t millis);
void Fake_delayus(uint32_t micros);

#endif
