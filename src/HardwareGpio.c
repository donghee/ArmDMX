#include "HardwareGpio.h"
#include "gpio.h"

void pinMode(uint8_t pin, uint8_t mode)
{
 	GPIOSetDir(PORT, pin, mode);
}

void digitalWrite(uint8_t pin, uint8_t  bitVal)
{
	GPIOSetValue(PORT, pin, bitVal);
}

void delayms(uint32_t millis)
{
  uint32_t delay = millis * ((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV / 1000) / 45);      // Release Mode (-Os)
  while (delay > 0)
  {
    __asm volatile ("nop");
    delay--;
  }
}

void delayus(uint32_t micros)
{
	uint32_t i;
	for (i=0; i< 45*micros; i++ ) {
	    __asm volatile ("nop");
	}

	/*
  uint32_t delay = micros * ((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV/ 1000000) / 45);      // Release Mode (-Os)
  while (delay > 0)
  {
    __asm volatile ("nop");
    delay--;
  }
  */
}
