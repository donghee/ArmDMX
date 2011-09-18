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
  int i;
  Strip* strip1;
  Strip* strip2;
  Strip* strip3;
  Strip* strip4;

  GPIOInit();

  GPIOSetDir( INDICATOR_LED_PORT, INDICATOR_LED_BIT, 1 );
  GPIOSetValue(INDICATOR_LED_PORT, INDICATOR_LED_BIT, ON);

  init_timer32(0, TIME_INTERVAL); // raise interrupt per 2.5 ms

  //DMXInit(250000);

  ch = get_dmx_channel();

  strip1 = Strip_new(60, 0,1);
  strip2 = Strip_new(60, 2,3);
  strip3 = Strip_new(60, 4,5);
  strip4 = Strip_new(60, 6,7);

  while (1)
  {
//	  ToggleGPIOBit(2,3);
//
	  for(i=0; i< 60;i++) {
		  Strip_setPixels(strip1, 0);
		  Strip_setPixel(strip1,i,16776960);

		  Strip_setPixels(strip2, 0);
		  Strip_setPixel(strip2,i,16776960);

		  Strip_setPixels(strip3, 0);
		  Strip_setPixel(strip3,i,16776960);

		  Strip_setPixels(strip4, 0);
		  Strip_setPixel(strip4,i, 16776960);


		  Strip_show(strip1);
		  Strip_show(strip2);
		  Strip_show(strip3);
		  Strip_show(strip4);
	  }
  }

  Strip_free(strip1);
  Strip_free(strip2);
  Strip_free(strip3);
  Strip_free(strip4);
  return 0;
}
