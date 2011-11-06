#include "driver_config.h"
#include "target_config.h"

#include "gpio.h"
#include "small_gpio.h"
#include "timer32.h"

#include "dmx.h"
#include "WS2801.h"
#include "WS2801_utils.h"
#include "switch.h"
#include "strip.h"

#include <math.h>

#define INDICATOR_LED_PORT 3
#define INDICATOR_LED_BIT 5

// Channel Info
// 1st - Red
// 2nd - Green
// 3nd - Blue
// 4th - Mode for animation
// 5th - Substrips Select [1..8]

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2
#define MODE_CHANNEL 3
#define SUBSTRIP_CHANNEL 4

// animation mode
#define DIRECT 0
#define DOTFLOW 1
#define RAINBOW 32
#define NOISE 124
#define SINEWAVE_DIMMING  125

// for dotflow speed
#define DOTFLOW_DEFAULT_SPEED 20

// start DMX channel
uint16_t DMX_channel;

//// SETUP
void Strip_setup() {
	strips[0] = Strip_new(160, 0,1);
	strips[1] = Strip_new(160, 2,3);
	strips[2] = Strip_new(160, 4,5);
	strips[3] = Strip_new(160, 6,7);

	// v
	strips[0]->substrips = 1; // number of substrips
	strips[0]->substrip_pixels = (uint8_t*) malloc(strips[0]->substrips * sizeof(uint8_t));
	strips[0]->substrip_pixels[0] = 100;

	// edge
	strips[1]->substrips = 8;
	strips[1]->substrip_pixels = (uint8_t*) malloc(strips[1]->substrips * sizeof(uint8_t));
	strips[1]->substrip_pixels[0] = 19;
	strips[1]->substrip_pixels[1] = 19;
	strips[1]->substrip_pixels[2] = 19;
	strips[1]->substrip_pixels[3] = 19;
	strips[1]->substrip_pixels[4] = 19;
	strips[1]->substrip_pixels[5] = 19;
	strips[1]->substrip_pixels[6] = 19;
	strips[1]->substrip_pixels[7] = 19;

	// face
	strips[2]->substrips = 4;
	strips[2]->substrip_pixels = (uint8_t*) malloc(strips[2]->substrips * sizeof(uint8_t));
	strips[2]->substrip_pixels[0] = 30;
	strips[2]->substrip_pixels[1] = 43;
	strips[2]->substrip_pixels[2] = 45;
	strips[2]->substrip_pixels[3] = 31;

	// reflective back
	strips[3]->substrips = 8;
	strips[3]->substrip_pixels = (uint8_t*) malloc(strips[3]->substrips * sizeof(uint8_t));
	strips[3]->substrip_pixels[0] = 20;
	strips[3]->substrip_pixels[1] = 20;
	strips[3]->substrip_pixels[2] = 20;
	strips[3]->substrip_pixels[3] = 20;
	strips[3]->substrip_pixels[4] = 20;
	strips[3]->substrip_pixels[5] = 20;
	strips[3]->substrip_pixels[6] = 20;
	strips[3]->substrip_pixels[7] = 20;
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

void DMX_setup()
{
	DMXInit(250000);
	DMX_channel = get_dmx_channel();
}

void Setup()
{
	GPIOInit();

	Strip_setup();
	Timer_setup();
	DMX_setup();
}


//// Set DMX data to strips!
void toggle_status_led()
{
	ToggleGPIOBit(INDICATOR_LED_PORT,INDICATOR_LED_BIT);
}

void Set_animation_mode(Strip** strips)
{
	strips[0]->mode = DMX_buf[DMX_channel+MODE_CHANNEL];
	strips[1]->mode = DMX_buf[DMX_channel+5+MODE_CHANNEL];
	strips[2]->mode = DMX_buf[DMX_channel+10+MODE_CHANNEL];
	strips[3]->mode = DMX_buf[DMX_channel+15+MODE_CHANNEL];
}

void Set_substrip(Strip** strips)
{
	strips[0]->mask = DMX_buf[DMX_channel+SUBSTRIP_CHANNEL];
	strips[1]->mask = DMX_buf[DMX_channel+5+SUBSTRIP_CHANNEL];
	strips[2]->mask = DMX_buf[DMX_channel+10+SUBSTRIP_CHANNEL];
	strips[3]->mask = DMX_buf[DMX_channel+15+SUBSTRIP_CHANNEL];
}

void set_substrip_color(Strip* strip,uint8_t strip_index, uint32_t color) {
	uint8_t j;
	uint8_t start_index = 0;

	for (j=0; j< strip_index; j++) {
		start_index += strip->substrip_pixels[j];
	}

	for (j=0; j< strip->substrip_pixels[strip_index]; j++) {
		Strip_setPixel(strip,start_index + j,color);
	}
}

void _set_mask(Strip* strip) {
	uint8_t k;

	for (k=0; k<strip->substrips; k++) {
		if ((strip->mask & (int) pow(2,k)) == 0) {
			set_substrip_color(strip, k,0); // turn off substrips
		}
	}
}

void Set_mask(Strip** strips)
{
	uint8_t j;

	for (j=0; j<NUMBER_OF_STRIP; j++) {
		_set_mask(strips[j]);
	}
}

void dotflow(Strip* strip, uint8_t tails)
{
	uint8_t i;
	Strip_setPixels(strip,0);

	for (i=0; i <tails; i++) {
		Strip_setPixel(strip,strip->cursor+i,strip->color);
	}
}


void Set_pixel(Strip** strips)
{
	  uint8_t j;

	  for(j=0; j<NUMBER_OF_STRIP; j++)
	  {
		  strip = strips[j];
		  if (strip->mode == DIRECT) {
			  Strip_setPixels(strip, strip->color);
		  } else if (strip->mode < DOTFLOW+31) {
			  strip->cursor_speed = (int) strip->mode;
			  if (strip->cursor >= strip->length) {
				  strip->cursor=0;
			  }
			  if (strip->cursor_speed < DOTFLOW_DEFAULT_SPEED) {
				  dotflow(strip,5); // 5 is default tail length.
			  }else {
				  dotflow(strip,strip->cursor_speed-DOTFLOW_DEFAULT_SPEED+5);
			  }
		  }
	  }
}

void Set_speed(Strip** strips)
{
	uint8_t j;
	uint8_t speed;
	for(j=0; j<NUMBER_OF_STRIP; j++)
	{
		strip = strips[j];
		if (strip->cursor >= strip->length)
		{
			strip->cursor=0;
		}

		if (strip->cursor_speed < DOTFLOW_DEFAULT_SPEED) { // 20 is threshold speed
			if (strip->frame_count >= (DOTFLOW_DEFAULT_SPEED - strip->cursor_speed)) {
				strip->cursor++;
				strip->frame_count = 0;
			} else {
				strip->frame_count++;
			}
		} else {
			strip->cursor = strip->cursor + strip->cursor_speed-DOTFLOW_DEFAULT_SPEED + 1;
		}
	}
}

uint32_t get_DMX_color(uint8_t strip_index) {
	return color(DMX_buf[DMX_channel+(strip_index*5)],DMX_buf[DMX_channel+(strip_index*5)+1],DMX_buf[DMX_channel+(strip_index*5)+2]);
}

void Set_color(Strip** strips)
{
	strips[0]->color = get_DMX_color(0);
	strips[1]->color = get_DMX_color(1);
	strips[2]->color = get_DMX_color(2);
	strips[3]->color = get_DMX_color(3);
}

int main (void) {
	Setup();

	while (1)
	{
		if (rx_count !=0) {
			Set_color(strips);
			Set_substrip(strips); // get sub strip channel!
			Set_animation_mode(strips);
		}
		Set_pixel(strips);
		Set_speed(strips);
		Set_mask(strips);

		Strip_shows(strips);
  }

  Strip_free(strips[0]);
  Strip_free(strips[1]);
  Strip_free(strips[2]);
  Strip_free(strips[3]);
  return 0;
}
