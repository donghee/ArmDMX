#include "HardwareGpio.h"
#include "gpio.h"

void pinMode(uint8_t pin, uint8_t mode)
{
	uint8_t PORT = pin/10;
	pin = pin%10;

 	GPIOSetDir(PORT, pin, mode);
}

void digitalWrite(uint8_t pin, uint8_t  bitVal)
{
	uint8_t PORT = pin/10;
	pin = pin%10;

	digitalPortPinWrite(PORT, pin, bitVal);
}

void digitalPortPinWrite(uint8_t port, uint8_t pin, uint8_t bitVal)
{
	GPIOSetValue(port, pin, bitVal);
}

uint8_t digitalPortPinRead(uint8_t port, uint8_t pin)
{

	uint8_t value;

	switch ( port )
	{
		case PORT0:
			value = LPC_GPIO0->MASKED_ACCESS[(1<<pin)] ? 1 : 0;
		break;
		case PORT1:
			value = LPC_GPIO1->MASKED_ACCESS[(1<<pin)] ? 1 : 0;
		break;
		case PORT2:
			value = LPC_GPIO2->MASKED_ACCESS[(1<<pin)] ? 1 : 0;
		break;
		case PORT3:
			value = LPC_GPIO3->MASKED_ACCESS[(1<<pin)] ? 1 : 0;
		break;
		default:
		  break;
	  }

	return value;
}

uint8_t digitalRead(uint8_t pin)
{
	uint8_t port = pin/10;
	pin = pin%10;

	digitalPortPinRead(port, pin);
}

/*
void delayms(uint32_t millis)
{
  uint32_t delay = millis * ((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV / 1000) / 45);      // Release Mode (-Os)
  while (delay > 0)
  {
    __asm volatile ("nop");
    delay--;
  }
}

*/

void delayms(uint32_t delayIn_ms) {
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 9);
	LPC_TMR32B0->TCR = 0x02; /* reset timer */
	LPC_TMR32B0->PR = 0x00; /* set prescaler to zero */
	LPC_TMR32B0->MR0 = delayIn_ms * ((SystemCoreClock
			/ LPC_SYSCON->SYSAHBCLKDIV) / 1000);
	LPC_TMR32B0->IR = 0xff; /* reset all interrrupts */
	LPC_TMR32B0->MCR = 0x04; /* stop timer on match */
	LPC_TMR32B0->TCR = 0x01; /* start timer */
	/* wait until delay time has elapsed */
	while (LPC_TMR32B0->TCR & 0x01)
		;
}

void delayus(uint32_t delayIn_ms) {
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 9);
	LPC_TMR32B0->TCR = 0x02; /* reset timer */
	LPC_TMR32B0->PR = 0x00; /* set prescaler to zero */
	LPC_TMR32B0->MR0 = delayIn_ms * ((SystemCoreClock
			/ LPC_SYSCON->SYSAHBCLKDIV) / 1000000);
	LPC_TMR32B0->IR = 0xff; /* reset all interrrupts */
	LPC_TMR32B0->MCR = 0x04; /* stop timer on match */
	LPC_TMR32B0->TCR = 0x01; /* start timer */
	/* wait until delay time has elapsed */
	while (LPC_TMR32B0->TCR & 0x01)
		;
}

/*

void delayus(uint32_t micros)
{

	uint32_t i;
	for (i=0; i< 45*micros; i++ ) {
	    __asm volatile ("nop");
	}


//
  uint32_t delay = micros * ((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV/ 1000000) / 45);      // Release Mode (-Os)
  while (delay > 0)
  {
    __asm volatile ("nop");
    delay--;
  }

}
*/
