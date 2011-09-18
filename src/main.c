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
  Strip* strip;

  GPIOInit();
//  GPIOSetDir( LED_PORT, LED_BIT, 1 );
//  GPIOSetValue(LED_PORT, LED_BIT, ON);

  GPIOSetDir( INDICATOR_LED_PORT, INDICATOR_LED_BIT, 1 );
  GPIOSetValue(INDICATOR_LED_PORT, INDICATOR_LED_BIT, ON);

  init_timer32(0, TIME_INTERVAL); // raise interrupt per 2.5 ms
  //enable_timer32(0);

  //DMXInit(250000);

  ch = get_dmx_channel();
  strip = Strip_new(300, 20,21);

  Strip_setPixels(strip, 0);
  Strip_show(strip);

  Strip_free(strip);

  strip = Strip_new(60, 20,21);

  while (1)
  {

	  for(i=0; i< 255;i++) {
	  Strip_setPixels(strip, 0);
	  Strip_setPixel(strip,i,16776960);
	  Strip_setPixel(strip,i+5,16776960);
	  Strip_show(strip);
//	  delayms(2);
	  }
	 // rainbow(strip,1);
	  //ToggleGPIOBit(INDICATOR_LED_PORT,INDICATOR_LED_BIT);
	  //delay32Ms(0,500);
//	  rainbow(strip,1);
//	  if (rx_count !=0) {

////		  Strip_setPixels(strip, color(DMX_buf[100], DMX_buf[101], DMX_buf[102]));
// 	  	  Strip_setPixels(strip, color(0,200,0));
// 		  Strip_show(strip);
//// 		  delayms(5);
////////
// 		  Strip_setPixels(strip, color(0,0,0));
// 		  Strip_show(strip);
// 		  delayms(5);



//	  }
  }

//  Strip_free(strip);
  return 0;
}
