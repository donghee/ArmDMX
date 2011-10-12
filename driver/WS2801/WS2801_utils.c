#include "WS2801_utils.h"
#include "WS2801.h"


void noise(Strip* self)
{
//	Strip_setPixel(strip, rand()); // TODO check, rand();
}
void rainbow(Strip* self, uint8_t wait)
{
	uint16_t i,j;
	for (j=0; j<256; j++) { // TOFIX: 256
		for (i =0; i< self->length; i++) {
			Strip_setPixel(self, i, wheel(((i*10)+j) %255));
		}
        Strip_show(self);
		delayms(wait);
	}
}

void rainbow2(Strip* self, uint8_t j, uint8_t length)
{
	uint16_t i;
	for (i =0; i< self->length; i++) {
		Strip_setPixel(self, i, wheel(((i*length)+j) %255));
	}
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

uint32_t interpolation(uint32_t color1, uint32_t color2)
{
	uint32_t color = color1- color2;
	if (color > 16777215) color = 16777215;
	if (color <0 ) color = 0;
	return color;
}
