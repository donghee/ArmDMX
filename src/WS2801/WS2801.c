#include "WS2801.h"

#define OUT 1

uint32_t color(uint8_t r, uint8_t g, uint8_t b)
{
	return (r<<16)|(g<<8)|b;
}

Strip* Strip_new(uint16_t led_size, uint8_t data_pin, uint8_t clock_pin)
{
	uint16_t i;

    Strip* self = (Strip*) malloc(sizeof(Strip));
    self->length = led_size;
    self->data_pin = data_pin;
    self->clock_pin = clock_pin;
    self->pixels = (uint32_t*) malloc(led_size * sizeof(uint32_t));
    
    for(i=0; i<led_size; i++)
	{
        self->pixels[i] = 0;
    }
    pinMode(data_pin, OUT);
    pinMode(clock_pin, OUT);
    
	digitalWrite(self->clock_pin, HIGH); // clock pull up


    return self;
}

void Strip_free(Strip* self)
{
    free(self->pixels);
    free(self);
}


void Strip_setPixel(Strip* self, uint16_t index, uint32_t color)
{
    if (index >= self->length) return;
    self->pixels[index] = color;
}

void Strip_setPixels(Strip* self, uint32_t color)
{
	uint16_t i;
	for (i=0; i< self->length; i++)
	{
		Strip_setPixel(self, i, color);
	}
}

void Strip_show(Strip* strip)
{
	uint16_t i;

	digitalWrite(strip->clock_pin, LOW);
	delayus(500);
	for (i = 0; i < strip->length; i++)
	{
		rgb_step(strip->pixels[i], strip->data_pin, strip->clock_pin);
	}
	digitalWrite(strip->clock_pin, HIGH);
}

void rgb_step(uint32_t color, uint8_t data_pin, uint8_t clock_pin)
{
	uint32_t i;
    for (i=0b100000000000000000000000; i>0; i>>=1) {
        digitalWrite(clock_pin, LOW);
        if (color & i)
            digitalWrite(data_pin, HIGH);
        else
            digitalWrite(data_pin, LOW);
        delayus(5); // TOFIX: delete
        digitalWrite(clock_pin, HIGH);    // latch on clock rise
        delayus(5);
	}
}
