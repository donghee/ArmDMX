#ifndef ___WS2801_H
#define ___WS2801_H

#include "HardwareUtils.h"

#include <stdlib.h>
#include "LPC11xx.h"

#include "driver_config.h"
#include "small_gpio.h"

typedef struct
{
	uint8_t data_pin;
	uint8_t clock_pin;
    uint16_t length;
    volatile uint32_t* pixels;

//    uint8_t* reds;
//    uint8_t* greens;
//    uint8_t* blues;
} Strip;


Strip* Strip_new(uint16_t led_size, uint8_t data_pin, uint8_t clock_pin);
void Strip_free(Strip* self);
void Strip_setPixel(Strip* self, uint16_t index, uint32_t color);
void Strip_setPixels(Strip* self, uint32_t color);
void Strip_show(Strip* strip);
void Strip_shows(Strip* strip1, Strip* strip2, Strip* strip3, Strip* strip4);


//void Strip_setPixelRGB(Strip* self, uint16_t index, uint8_t red, uint8_t blue, uint8_t green);
//void Strip_setPixelsRGB(Strip* self, uint8_t red, uint8_t blue, uint8_t green);

uint32_t color(uint8_t r, uint8_t g, uint8_t b);
void rgb_step(uint32_t color, uint8_t data_pin, uint8_t clock_pin);


//#define COLOR (r<<16)|(g<<8)|b;
#endif
