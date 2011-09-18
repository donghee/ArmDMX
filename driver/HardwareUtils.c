#include "HardwareUtils.h"

void pinMode(uint8_t pin, uint8_t mode)
{
	uint8_t PORT = pin/10;
	pin = pin%10;

 	GPIOSetDir(PORT, pin, mode);
}

void portPinMode(uint8_t port, uint8_t pin, uint8_t mode)
{
 	GPIOSetDir(port, pin, mode);
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

	return digitalPortPinRead(port, pin);
}

void delayms(uint32_t millis) {
	/* use time #0 */
	delay32Ms(0,millis);
}

void delayus(uint32_t micros) {
    /* setup timer #0 for delay */
    LPC_TMR32B0->TCR = 0x02;		/* reset timer */
    LPC_TMR32B0->PR  = 0x00;		/* set prescaler to zero */
    LPC_TMR32B0->MR0 = micros * ((SystemCoreClock/(LPC_TMR32B0->PR+1)) / 1000);
    LPC_TMR32B0->IR  = 0xff;		/* reset all interrrupts */
    LPC_TMR32B0->MCR = 0x04;		/* stop timer on match */
    LPC_TMR32B0->TCR = 0x01;		/* start timer */

    /* wait until delay time has elapsed */
    while (LPC_TMR32B0->TCR & 0x01);
}
