/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>
#include "dmx.h"
#include "gpio.h"
#include "HardwareGpio.h"
#include "WS2801/WS2801.h"
#include "WS2801/utils.h"

#define LED_PORT 0
#define LED_BIT 7
#define LED_ON 1
#define LED_OFF 0


// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

// TODO: insert other definitions and declarations here

#define DMX_NUMBER 2
uint32_t dmx_1_value;

int main(void) {
	int i;
	Strip* strip;
	Strip* strip1;
	GPIOSetDir(LED_PORT, LED_BIT, 1);
 	GPIOSetValue(LED_PORT, LED_BIT, LED_ON );
	DMXInit(250000);

	strip = Strip_new(1,7,6);
	strip1 = Strip_new(1,27,26);

	while(1){
		rainbow(strip,100);
		rainbow(strip1,100);

		if (rx_count !=0) {

//			i = 100;
//			Strip_setPixel(strip,0, color(DMX_buf[i],DMX_buf[i+1],DMX_buf[i+2]));
//			i = 104;
//			Strip_setPixel(strip,1, color(DMX_buf[i],DMX_buf[i+1],DMX_buf[i+2]));
//			i = 108;
//			Strip_setPixel(strip,2, color(DMX_buf[i],DMX_buf[i+1],DMX_buf[i+2]));
//			Strip_show(strip);
		}
	}
	Strip_free(strip);
	return 0 ;
}
