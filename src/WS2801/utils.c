#include "utils.h"
#include "WS2801.h"

void rainbow(Strip* self, uint8_t wait)
{
	uint16_t i,j;
	for (j=0; j<256; j++) { // TOFIX: 256
		for (i =0; i< self->length; i++) {
			Strip_setPixel(self, i, wheel(((i*40)+j) %255));
		}
        Strip_show(self);
		delayms(wait);
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
