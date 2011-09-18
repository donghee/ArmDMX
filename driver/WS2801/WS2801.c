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

//    self->reds = (uint8_t*) malloc(led_size * sizeof(uint8_t));
//    self->blues = (uint8_t*) malloc(led_size * sizeof(uint8_t));
//    self->greens = (uint8_t*) malloc(led_size * sizeof(uint8_t));

    for(i=0; i<led_size; i++)
	{
        self->pixels[i] = 0;
//        self->reds[i] = 0;
//        self->blues[i] = 0;
//        self->greens[i] = 0;
    }
    portPinMode(LED_STRIP_PORT, data_pin, OUT);
    portPinMode(LED_STRIP_PORT, clock_pin, OUT);
    
    return self;
}

void Strip_free(Strip* self)
{
    free(self->pixels);
//    free(self->reds);
//    free(self->blues);
//    free(self->greens);
    free(self);
}


void Strip_setPixel(Strip* self, uint16_t index, uint32_t color)
{
    //if (index >= self->length) return;
    self->pixels[index] = color;
}
//
//void Strip_setPixelRGB(Strip* self, uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
//{
//	self->reds[index] = red;
//	self->greens[index] = green;
//	self->blues[index] = blue;
//}


void Strip_setPixels(Strip* self, uint32_t color)
{
	uint16_t i;
	for (i=0; i< self->length; i++)
	{
		Strip_setPixel(self, i, color);
	}
}
//
//void Strip_setPixelsRGB(Strip* self, uint8_t red, uint8_t green, uint8_t blue)
//{
//	uint16_t i;
//	for (i=0; i< self->length; i++)
//	{
//		Strip_setPixelRGB(self, i, red, green, blue);
//	}
//}

void Strip_show(Strip* strip)
{
	uint16_t i;

//	clock low _
	LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<(strip->clock_pin)] = (0<<(strip->clock_pin));
	delayms(1);

	for (i = 0; i < strip->length; i++)
	{
		rgb_step(strip->pixels[i], strip->data_pin, strip->clock_pin);
	}
	// clock low _
	LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<(strip->clock_pin)] = (1<<(strip->clock_pin));
}

void rgb_step(uint32_t color, uint8_t data_pin, uint8_t clock_pin)
{
	uint32_t i;
    for (i=0b100000000000000000000000; i>0; i>>=1) {
    	// clock low _
//    	GPIOSetValue(LED_STRIP_PORT,clock_pin,LOW);
    	// use LPC_GPIO MASKED ACCESS for speed up;
    	LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<clock_pin] = (0<<clock_pin);
    	// data high or low -_
//     	GPIOSetValue(LED_STRIP_PORT,data_pin,(1<<!(color&i)));
    	LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<data_pin] = ((1<<!(color & i)<< data_pin));
    	// clock low _
//    	GPIOSetValue(LED_STRIP_PORT,clock_pin,HIGH);
    	LPC_GPIO[LED_STRIP_PORT]->MASKED_ACCESS[1<<clock_pin] = (1<<clock_pin);
	}
}
