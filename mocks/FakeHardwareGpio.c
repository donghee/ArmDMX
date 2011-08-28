#include "FakeHardwareGpio.h"

void Fake_pinMode(uint8_t pin, uint8_t mode)
{
}

void Fake_digitalWrite(uint8_t pin, uint8_t  bitVal)
{
}

void Fake_delayms(uint32_t millis)
{
}

void Fake_delayus(uint32_t micros) 
{
}

void (*delayus)(uint32_t) = Fake_delayus;
void (*delayms)(uint32_t) = Fake_delayms;
void (*digitalWrite)(uint8_t, uint8_t) = Fake_digitalWrite;
void (*pinMode)(uint8_t, uint8_t) = Fake_pinMode;
