#include "FakeHardwareGpio.h"

static void Fake_delayms(uint8_t p, uint32_t millis)
{
}

static void Fake_delayus(uint8_t p, uint32_t micros) 
{
}

void Fake_GPIOSetDir(uint8_t port, uint8_t pin, uint8_t mode) 
{
}

void (*delay32Us)(uint8_t, uint32_t) = Fake_delayus;
void (*delay32Ms)(uint8_t, uint32_t) = Fake_delayms;
void (*GPIOSetDir)(uint8_t, uint8_t, uint8_t)  = Fake_GPIOSetDir;


