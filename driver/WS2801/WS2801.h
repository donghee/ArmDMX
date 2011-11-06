#ifndef ___WS2801_H
#define ___WS2801_H

#include "LPC11xx.h"
#include "HardwareUtils.h"

typedef struct
{
	uint8_t data_pin;
	uint8_t clock_pin;
    uint16_t length;
    volatile uint32_t* pixels;

    uint32_t color;
    uint8_t mode; // animation mode;

    uint16_t frame_count;
    uint8_t cursor; // dotflow cursor;
    uint8_t cursor_speed; // dotflow speed

    uint8_t substrips;
    uint8_t* substrip_pixels;
    uint8_t mask; // for selecting substrip
} Strip;


Strip* Strip_new(uint16_t led_size, uint8_t data_pin, uint8_t clock_pin);
void Strip_free(Strip* self);
void Strip_setPixel(Strip* self, uint16_t index, uint32_t color);
void Strip_setPixels(Strip* self, uint32_t color);

uint32_t Strip_getPixel(Strip* self, uint16_t index);
void Strip_show(Strip* strip);
void Strip_shows(Strip** strips);

uint32_t color(uint8_t r, uint8_t g, uint8_t b);
void rgb_step(uint32_t color, uint8_t data_pin, uint8_t clock_pin);


#endif
