#include "LPC11xx.h"
#include "dmx.h"

void UART_IRQHandler(void)
{
	static uint8_t iid;
	while (((iid = LPC_UART->IIR) & 1) == 0)
	{
		if ((iid & 0x0E) == IIR_CTI) {
			LPC_UART->LSR;
			LPC_UART->RBR;
			rx_count=0;
		}
		else
			do
			{
				DMX_buf[rx_count] = LPC_UART->RBR;
				if(rx_count < DMX_SIZE) {
					rx_count++;
				}
			} while(LPC_UART->LSR & LSR_RDR);
	}
}

void UARTInit(uint32_t baudrate)
{
  uint32_t Fdiv;
  uint32_t regVal;

  rx_count = 0;

  NVIC_DisableIRQ(UART_IRQn);

  LPC_IOCON->PIO1_6 &= ~0x07;    /*  UART I/O config */
  LPC_IOCON->PIO1_6 |= 0x01;     /* UART RXD */
  LPC_IOCON->PIO1_7 &= ~0x07;
  LPC_IOCON->PIO1_7 |= 0x01;     /* UART TXD */

  /* Enable UART clock */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);
  LPC_SYSCON->UARTCLKDIV = 0x1;     /* divided by 1 */

  LPC_UART->LCR = 0x87;             /* 8 bits, no Parity, 2 Stop bit */
  regVal = LPC_SYSCON->UARTCLKDIV;
// CodeRed - variable name changed in CMSIS 1.3
//  Fdiv = ((SystemAHBFrequency/regVal)/16)/baudrate ;	/*baud rate */
  Fdiv = (((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV)/regVal)/16)/baudrate ;	/*baud rate */

  LPC_UART->DLM = Fdiv / 256;
  LPC_UART->DLL = Fdiv % 256;
  LPC_UART->LCR = 0x03;		/* DLAB = 0 */
  LPC_UART->FCR = 0x87;		/* Enable and reset TX and RX FIFO. */

  /* Read to clear the line status. */
  regVal = LPC_UART->LSR;

  /* Ensure a clean start, no data in either TX or RX FIFO. */
  while ( (LPC_UART->LSR & (LSR_THRE|LSR_TEMT)) != (LSR_THRE|LSR_TEMT) );
  while ( LPC_UART->LSR & LSR_RDR )
  {
	regVal = LPC_UART->RBR;	/* Dump data from RX FIFO */
  }

  /* Enable the UART Interrupt */
  NVIC_EnableIRQ(UART_IRQn);

#if TX_INTERRUPT
  LPC_UART->IER = IER_RBR | IER_THRE | IER_RLS;	/* Enable UART interrupt */
#else
  LPC_UART->IER = IER_RBR | IER_RLS;	/* Enable UART interrupt */
#endif
  return;
}
