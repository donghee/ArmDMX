#include "utils.h"
#include "WS2801.h"

void rainbow(uint8_t wait)
{
	uint8_t i,j;
	for (j=0; j<256; j++) {
		for (i =0; i< pixels_length; i++) {
			set_pixel_color(i, wheel(((i*40)+j) %255));
		}
		strip_show();
		delayms(wait);
	}
}


struct strip* make_strips(uint8_t _channels, uint16_t led_size)
{
	uint16_t i;
	uint8_t ch;

	channels = _channels;

	struct strip* s = (struct strip*) malloc(channels*sizeof(struct strip));

	for(ch=0;ch<channels; ch++) {
		s[ch].length = led_size;
		s[ch].pixels = (uint32_t*) malloc(led_size * sizeof(uint32_t));
		for(i=0; i<led_size; i++)
		{
			s[ch].pixels[i] = 0;
		}
	}
	return s;
}


void set_color(struct strip* self, uint16_t index, uint32_t color)
{
	self->pixels[index] = color;
}


void rgb_step_strip(uint8_t data_pin, uint8_t clock_pin, uint32_t color)
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

void show(struct strip* strips)
{
	uint16_t ch, i;
	uint8_t data_pin, clock_pin;
	uint32_t* pixels;

	for (ch=0; i < channels; ch++) {
		data_pin = strips[ch].data_pin;
		clock_pin = strips[ch].clock_pin;
		pixels_length = strips[ch].length;

		digital_write(clock_pin, LOW);
		delayus(500);
		for (i = 0; i < pixels_length; i++)
		{
			rgb_step_strip(data_pin, clock_pin, strips[ch].pixels[i]);
		}
		digital_write(clock_pin, LOW);
	}

}

void set_data_clock_pin(struct strip* self, uint8_t data_pin, uint8_t clock_pin)
{
	self->data_pin = data_pin;
	self->clock_pin = clock_pin;
}

void free_strips(struct strip* strips)
{
	uint8_t i;
	for (i=0; i<channels; i++)
	{
		free(strips[i].pixels);
	}
	free(strips);
}
