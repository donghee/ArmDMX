#include "WS2801.h"

#define OUT 1
#define LED_STRIP_PORT 2

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
    portPinMode(LED_STRIP_PORT, data_pin, OUT);
    portPinMode(LED_STRIP_PORT, clock_pin, OUT);
    
    return self;
}

void Strip_free(Strip* self)
{
    free(self->pixels);
    free(self);
}


void Strip_setPixel(Strip* self, uint16_t index, uint32_t color)
{
//    if (index >= self->length) return;
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

//	clock low _
	LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<(strip->clock_pin)] = (0<<(strip->clock_pin));
	//delayms(1);
	delay32Us(0,500);

	for (i = 0; i < strip->length; i++)
	{
		rgb_step(strip->pixels[i], strip->data_pin, strip->clock_pin);
	}
	// clock low _
	LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<(strip->clock_pin)] = (0<<(strip->clock_pin));
}

void rgb_step(uint32_t color, uint8_t data_pin, uint8_t clock_pin)
{
	uint8_t i;
    for (i=23; i>-1; i--) {
    	LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<clock_pin] = (0<<clock_pin);
    	LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<data_pin] = ((color>> i)<< data_pin);
    	LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<clock_pin] = (1<<clock_pin);
	}
}


void Strip_shows(Strip* strip1, Strip* strip2, Strip* strip3, Strip* strip4)
{
	uint16_t i;

	//	clock low _
	LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<(strip1->clock_pin) | 1 << (strip2->clock_pin) |
	                                        1<<(strip3->clock_pin) | 1 << (strip4->clock_pin)] = 0;
	//delayms(1);
	delay32Us(0,500);

	for (i = 0; i < strip1->length; i++) // TODO length is largest length of strips
	{
		rgb_steps(i, strip1, strip2, strip3, strip4);
	}
	// clock low _
	// LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<(strip->clock_pin)] = (0<<(strip->clock_pin));

	LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<(strip1->clock_pin) | 1 << (strip2->clock_pin) |
	                                        1<<(strip3->clock_pin) | 1 << (strip4->clock_pin)] = 0;
}

void rgb_steps(uint16_t index, Strip* strip1, Strip* strip2, Strip* strip3, Strip* strip4)
{
	uint32_t i;
    for (i=23; i>=0; i--) {
    	LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<(strip1->clock_pin) | 1 << (strip2->clock_pin) |
    	                                        1<<(strip3->clock_pin) | 1 << (strip4->clock_pin)] = 0;

    	LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<(strip1->data_pin) | 1 << (strip2->data_pin) |
    	                                        1<<(strip3->data_pin) | 1 << (strip4->data_pin)] =
    	                                        		(strip1->pixels[index]>> i) << (strip1->data_pin) |
    	                                        		(strip2->pixels[index]>> i) << (strip2->data_pin) |
    	                                        		(strip3->pixels[index]>> i) << (strip3->data_pin) |
    	                                        		(strip4->pixels[index]>> i) << (strip4->data_pin) ;

    	LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<(strip1->clock_pin) | 1 << (strip2->clock_pin) |
    	                                        1<<(strip3->clock_pin) | 1 << (strip4->clock_pin)] = 0xff;
	}
}
