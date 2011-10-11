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

#define LED_PORT 0
#define LED_BIT 7


int main (void) {
  int ch;
  uint32_t i;
  uint32_t j;

  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint16_t strip_speed;
  uint8_t strip_mode;
  uint8_t strip_dimming;

  uint32_t c;
  //red=200;green=0;blue=0;strip_speed=0;strip_mode=0;strip_dimming=0;c=color(red,green,blue);

  Strip* strip1;
  Strip* strip2;
  Strip* strip3;
  Strip* strip4;

  GPIOInit();

  GPIOSetDir( INDICATOR_LED_PORT, INDICATOR_LED_BIT, 1 );
  GPIOSetValue(INDICATOR_LED_PORT, INDICATOR_LED_BIT, ON);

  init_timer32(0, TIME_INTERVAL); // raise interrupt per 2.5 ms

  DMXInit(250000);

  ch = get_dmx_channel();

  strip1 = Strip_new(256, 0,1);
  strip2 = Strip_new(256, 2,3);
  strip3 = Strip_new(256, 4,5);
  strip4 = Strip_new(256, 6,7);

  i = 0;

  while (1)
  {
 	  ToggleGPIOBit(INDICATOR_LED_PORT,INDICATOR_LED_BIT);
	  // update strip properties
	  if (rx_count !=0) {
		  red = DMX_buf[100]; // ch
		  green = DMX_buf[101]; // ch +1
		  blue = DMX_buf[102];
		  strip_mode = DMX_buf[103];  // ch + 3
		  strip_speed = DMX_buf[104]+1; // ch + 4
		  strip_dimming = DMX_buf[105]; // ch + 5
		  c = color(red, green, blue);
	  }
//
//	  // set strip mode
	  if (strip_mode == 0) {
		  Strip_setPixels(strip1,c);
		  Strip_setPixels(strip2,c);
		  Strip_setPixels(strip3,c);
		  Strip_setPixels(strip4,c);

		  Strip_show(strip1);
		  Strip_show(strip2);
		  Strip_show(strip3);
		  Strip_show(strip4);

	  } else if (strip_mode == 1) {
		  if (i >= strip1->length) {
			  i=0;
		  }

		  Strip_setPixels(strip1, 0);
		  Strip_setPixel(strip1,i,c);

//		  for(j=0; j<20; j++) {
//			  Strip_setPixel(strip1,i+j,interpolation(c,4));
//		  }
//		  Strip_setPixels(strip2, 0);
//		  Strip_setPixel(strip2,i,c);
//
//		  Strip_setPixels(strip3, 0);
//		  Strip_setPixel(strip3,i,c);
////
//		  Strip_setPixels(strip4, 0);
//		  Strip_setPixel(strip4,i, c);

		  Strip_show(strip1);
		  Strip_show(strip2);
		  Strip_show(strip3);
		  Strip_show(strip4);
//		  delayms(strip_speed);
		  i++;
	  }
  }

  Strip_free(strip1);
  Strip_free(strip2);
  Strip_free(strip3);
  Strip_free(strip4);
  return 0;
}
