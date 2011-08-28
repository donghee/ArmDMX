#ifndef ___WS2801_H__
#define ___WS2801_H__

/* #ifdef WIN32 */
#include "HardwareGpio.h"
/* #else */
/* 	#include "../_gpio.h" */
/* #endif */

#define RED 2
#define GREEN 1
#define BLUE 0

#include <stdlib.h>
#include "LPC11xx.h"

uint32_t color(uint8_t r, uint8_t g, uint8_t b);


typedef struct
{
	uint8_t data_pin;
	uint8_t clock_pin;
    uint16_t length;
    uint32_t* pixels;
} Strip;


Strip* Strip_new(uint16_t led_size, uint8_t data_pin, uint8_t clock_pin);
void Strip_free(Strip* self);
void Strip_setPixel(Strip* self, uint16_t index, uint32_t color);


void Strip_show(Strip* strip);
void rgb_step(uint32_t color, uint8_t data_pin, uint8_t clock_pin);


#endif
