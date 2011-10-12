#include "driver_config.h"
#include "target_config.h"

#include "gpio.h"
#include "small_gpio.h"
#include "timer32.h"

#include "dmx.h"
#include "WS2801.h"
#include "WS2801_utils.h"
#include "switch.h"

#define INDICATOR_LED_PORT 3
#define INDICATOR_LED_BIT 5

// animation mode
#define DIRECT 0
#define DOTFLOW 1
#define RAINBOW 32
#define NOISE 124
#define SINEWAVE_DIMMING  125

// DMX first channel
uint8_t DMX_channel;

// LED strips
Strip* strip1;
Strip* strip2;
Strip* strip3;
Strip* strip4;

Strip* strip; /* temp strip variable */

void Strip_setup() {
	  strip1 = Strip_new(160, 0,1);
	  strip2 = Strip_new(160, 2,3);
	  strip3 = Strip_new(160, 4,5);
	  strip4 = Strip_new(160, 6,7);
}

void DMX_setup()
{
	  DMXInit(250000);
	  DMX_channel = get_dmx_channel();
}

void Status_led_setup()
{
	  GPIOSetDir(INDICATOR_LED_PORT, INDICATOR_LED_BIT, 1 );
	  GPIOSetValue(INDICATOR_LED_PORT, INDICATOR_LED_BIT, ON);
}

void Timer_setup()
{
	init_timer32(0, TIME_INTERVAL); // raise interrupt per 2.5 ms
}

void Setup()
{
	GPIOInit();
	Strip_setup();
	DMX_setup();
	Status_led_setup();
	Timer_setup();
}

void Control_status_led()
{
	ToggleGPIOBit(INDICATOR_LED_PORT,INDICATOR_LED_BIT);
}

void Control_animation_mode()
{
	DMX_channel = 100;
	strip1->mode = DMX_buf[DMX_channel+3];
	strip2->mode = DMX_buf[DMX_channel+5+3];
	strip3->mode = DMX_buf[DMX_channel+10+3];
	strip4->mode = DMX_buf[DMX_channel+15+3];
}

void dotflow(Strip* strip,uint8_t dotsize,uint8_t cursor, uint32_t color)
{
	Strip_setPixels(strip1,0);
	Strip_setPixel(strip1,cursor,color);
}


void Control_color()
{
	static int dotsize, rainbow_length;

	strip = strip1;

	if (strip->mode == DIRECT ) {
		Strip_setPixels(strip, strip->color);
	} else if (strip->mode < DOTFLOW+31) {
		dotsize = strip->mode;
		dotflow(strip, dotsize, strip->cursor,strip->color);
	} else if (strip->mode < RAINBOW+32) {
		rainbow_length = strip->mode;
		rainbow2(strip, strip->cursor, rainbow_length);
	} else if (strip->mode == NOISE)
	{
		noise(strip);
	}

	strip = strip2;

	if (strip->mode == DIRECT ) {
		Strip_setPixels(strip, strip->color);
	} else if (strip->mode < DOTFLOW+31) {
		dotsize = strip->mode;
		dotflow(strip, dotsize, strip->cursor,strip->color);
	} else if (strip->mode < RAINBOW+32) {
		rainbow_length = strip->mode;
		rainbow2(strip, strip->cursor, rainbow_length);
	} else if (strip->mode == NOISE)
	{
		noise(strip);
	}

	strip = strip3;

	if (strip->mode == DIRECT ) {
		Strip_setPixels(strip, strip->color);
	} else if (strip->mode < DOTFLOW+31) {
		dotsize = strip->mode;
		dotflow(strip, dotsize, strip->cursor,strip->color);
	} else if (strip->mode < RAINBOW+32) {
		rainbow_length = strip->mode;
		rainbow2(strip, strip->cursor, rainbow_length);
	} else if (strip->mode == NOISE)
	{
		noise(strip);
	}

	strip = strip4;
	if (strip->mode == DIRECT ) {
		Strip_setPixels(strip, strip->color);
	} else if (strip->mode < DOTFLOW+31) {
		dotsize = strip->mode;
		dotflow(strip, dotsize, strip->cursor,strip->color);
	} else if (strip->mode < RAINBOW+32) {
		rainbow_length = strip->mode;
		rainbow2(strip, strip->cursor, rainbow_length);
	} else if (strip->mode == NOISE)
	{
		noise(strip);
	}
}

void Control_dimming()
{
}

void Control_speed()
{
	if (strip1->cursor == strip1->length)
	{
		strip1->cursor=0;
	}

	if (strip2->cursor == strip2->length)
	{
		strip2->cursor=0;
	}

	if (strip3->cursor == strip3->length)
	{
		strip3->cursor=0;
	}

	if (strip4->cursor == strip4->length)
	{
		strip4->cursor=0;
	}

	strip1->cursor++;
	strip2->cursor++;
	strip3->cursor++;
	strip4->cursor++;


}

int main (void) {
	uint8_t strip_mode, strip_speed, strip_dimming;
	uint8_t i;
	uint32_t c;

	Setup();

	while (1)
	{
//		if (rx_count !=0) {
//			//strip = strip1;
//			strip1->color = color(DMX_buf[DMX_channel],DMX_buf[DMX_channel+1],DMX_buf[DMX_channel+2]);
////			strip = strip2;
////			strip->color = color(DMX_buf[DMX_channel+5],DMX_buf[DMX_channel+5+1],DMX_buf[DMX_channel+5+2]);
////			strip = strip3;
////			strip->color = color(DMX_buf[DMX_channel+10],DMX_buf[DMX_channel+10+1],DMX_buf[DMX_channel+10+2]);
////			strip = strip4;
////			strip->color = color(DMX_buf[DMX_channel+15],DMX_buf[DMX_channel+15+1],DMX_buf[DMX_channel+15+2]);
//			Control_status_led();
//			Control_animation_mode();
//		}
//
//		Control_color();
//		Control_dimming();
//		Control_speed();

		  if (rx_count !=0) {
			  ToggleGPIOBit(INDICATOR_LED_PORT,INDICATOR_LED_BIT);

			  strip_mode = DMX_buf[103];  // ch + 3
			  strip_speed = DMX_buf[104]+1; // ch + 4
			  strip_dimming = DMX_buf[105]; // ch + 5
			  c = color(DMX_buf[100], DMX_buf[101],DMX_buf[102]);
		  }
		  if (strip_mode == 0) {
			  Strip_setPixels(strip1,c);
			  Strip_setPixels(strip2,c);
			  Strip_setPixels(strip3,c);
			  Strip_setPixels(strip4,c);

			  Strip_shows(strip1, strip2, strip3, strip4);

		  } else if (strip_mode == 1) {
			  if (i >= strip1->length) {
				  i=0;
			 }

			  Strip_setPixels(strip1, 0);
			  Strip_setPixel(strip1,i,c);

			  Strip_setPixels(strip2, 0);
			  Strip_setPixel(strip2,i,c);

			  Strip_setPixels(strip3, 0);
			  Strip_setPixel(strip3,i,c);

			  Strip_setPixels(strip4, 0);
			  Strip_setPixel(strip4,i, c);

			  Strip_shows(strip1, strip2, strip3, strip4);
			  i++;
		  }
  }

  Strip_free(strip1);
  Strip_free(strip2);
  Strip_free(strip3);
  Strip_free(strip4);
  return 0;
}
