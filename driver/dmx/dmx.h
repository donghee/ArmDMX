/*
 * dmx.h
 *
 *  Created on: 2011. 8. 16.
 *      Author: Future Electronics Technology Mixer
 */

#ifndef __DMX_H
#define __DMX_H

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define IER_RBR		0x01
#define IER_RLS		0x04

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80
#define DMX_SIZE	513

void DMXInit(uint32_t baudrate);
void UART_IRQHandler(void);

#endif /* DMX_H_ */

uint32_t rx_count;
uint8_t DMX_buf[DMX_SIZE];
uint8_t rx_buf;

volatile uint32_t UARTStatus;
