#include "WS2801.h"

#define OUT 1

uint32_t color(uint8_t r, uint8_t g, uint8_t b)
{
	return (r<<16)|(g<<8)|b;
}

uint32_t wheel(uint8_t position)
{
	if ( position <= 85) {
		return color(position*3, 255-position*3, 0);
	} else if (position <= 170) {
		position -=85;
		return color(255-position*3,0,position*3);
	} else {
		position -=170;
		return color(0,position*3, 255-position*3	);
	}
}

void make_strip(uint16_t size)
{
	uint16_t i;
	pixels_length = size;
	pixels = (uint32_t*) malloc(size * sizeof(uint32_t));
	for(i=0; i<size; i++)
	{
		set_pixel_color(i,0);
	}
}

void free_strip()
{
	free(pixels);
}

void set_pixel_color(uint16_t index, uint32_t color)
{
	if (index >= pixels_length) return;
	pixels[index] = color;
}

void ws2801_setup(uint16_t size, uint8_t _data_pin, uint8_t _clock_pin)
{
	data_pin = _data_pin;
	clock_pin = _clock_pin;
	pin_mode(data_pin, OUT);
	pin_mode(clock_pin, OUT);
	make_strip(size);
}

void strip_show()
{
	uint16_t i;

	digital_write(clock_pin, LOW);
	delayus(500);
	for (i = 0; i < pixels_length; i++)
	{
		rgb_step(pixels[i]);
	}
	digital_write(clock_pin, LOW);
}

void rgb_step(uint32_t color)
{
	uint32_t i;
    for (i=0b100000000000000000000000; i>0; i>>=1) {
        digital_write(clock_pin, LOW);
        if (color & i)
            digital_write(data_pin, HIGH);
        else
            digital_write(data_pin, LOW);
        digital_write(clock_pin, HIGH);    // latch on clock rise
	}
}
