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
#include "eeprom/eeprom.h"
#include "utils/switch.h"

#define LED_PORT 0
#define LED_BIT 7

#define INDICATOR_LED_PORT 3
#define INDICATOR_LED_BIT 5

#define LED_ON 1
#define LED_OFF 0

__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

#define DMX_NUMBER 2
uint32_t dmx_1_value;

int main(void) {
	int ch;
	int i;
	uint8_t value;
	Strip* strip;
	Strip* strip1;
	GPIOSetDir(LED_PORT, LED_BIT, 1);
 	GPIOSetValue(LED_PORT, LED_BIT, LED_ON );

 	GPIOSetDir(INDICATOR_LED_PORT, INDICATOR_LED_BIT, 1);
 	GPIOSetValue(INDICATOR_LED_PORT, INDICATOR_LED_BIT, LED_ON );

	DMXInit(250000);

	ch = get_channel();
	strip = Strip_new(256,20,21);
	while(1){
	//	rainbow(strip,10);

		for(i =0; i < 250; i++) {
			Strip_setPixels(strip, color(0,0,0));
			Strip_setPixel(strip,i, color(255,255,255));
			Strip_setPixel(strip,i+1, color(255,255,255));
			Strip_setPixel(strip,i+2, color(255,255,255));
			Strip_show(strip);
			delayms(5000);
		}

		if (rx_count !=0) {

			//Strip_setPixel(strip,0, color(DMX_buf[ch],DMX_buf[ch+1],DMX_buf[ch+2]));
			//Strip_setPixels(strip, color(DMX_buf[ch],DMX_buf[ch+1],DMX_buf[ch+2]));

			//ch = 110;
//			Strip_setPixel(strip1,0, color(DMX_buf[ch],DMX_buf[ch+1],DMX_buf[ch+2]));
			//Strip_setPixels(strip1, color(DMX_buf[ch],DMX_buf[ch+1],DMX_buf[ch+2]));

		//	i = 110;
		//	Strip_setPixel(strip,2, color(DMX_buf[i],DMX_buf[i+1],DMX_buf[i+2]));

			//Strip_show(strip);
			//Strip_show(strip1);
		}
	}
	Strip_free(strip);
	//Strip_free(strip1);
	return 0 ;
}
