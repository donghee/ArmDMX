#ifndef ___WS2801_H__
#define ___WS2801_H__

#ifdef WIN32
	#include "gpio.h"
#else
	#include "../_gpio.h"
#endif

#define RED 2
#define GREEN 1
#define BLUE 0

#include <stdlib.h>
#include "LPC11xx.h"

uint32_t color(uint8_t r, uint8_t g, uint8_t b);
uint32_t wheel(uint8_t position);

uint32_t* pixels;
uint16_t pixels_length;
uint8_t data_pin;
uint8_t clock_pin;


struct strip
{
	uint8_t data_pin;
	uint8_t clock_pin;
    uint16_t length;
    uint32_t* pixels;
};

//struct strip *strips;

void ws2801_setup(uint16_t size, uint8_t data_pin, uint8_t clock_pin);
void make_strip(uint16_t size);
void free_strip();

void set_pixel_color(uint16_t index, uint32_t color);

void strip_show();
void rgb_step(uint32_t color);
uint8_t get_graydata(uint32_t color, uint8_t rgb);

#endif
