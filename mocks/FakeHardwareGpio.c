#include "FakeHardwareGpio.h"

void Fake_pinMode(uint8_t pin, uint8_t mode)
{
}

void Fake_portPinMode(uint8_t port, uint8_t pin, uint8_t mode)
{
}

void Fake_digitalWrite(uint8_t pin, uint8_t  bitVal)
{
}

uint8_t Fake_digitalRead(uint8_t pin)
{
    return LOW;
}

void Fake_delayms(uint8_t p, uint32_t millis)
{
}

void Fake_delayus(uint8_t p, uint32_t micros) 
{
}

void (*delay32Us)(uint8_t, uint32_t) = Fake_delayus;
void (*delay32Ms)(uint8_t, uint32_t) = Fake_delayms;
void (*digitalWrite)(uint8_t, uint8_t) = Fake_digitalWrite;
uint8_t (*digitalRead)(uint8_t) = Fake_digitalRead;
void (*pinMode)(uint8_t, uint8_t) = Fake_pinMode;
void (*portPinMode)(uint8_t, uint8_t, uint8_t) = Fake_portPinMode;
