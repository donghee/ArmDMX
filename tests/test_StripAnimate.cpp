#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
//#include "WS2801.h"
//#include "LPC11xx.h"
//#include "gpio.h"
}

TEST_GROUP(StripAnimate)
{
	void setup()
    {
    }

    void teardown()
    {
    }
};

/*
TEST(StripAnimate, a)
{
    LONGS_EQUAL(0, color(0x00, 0x00,0x00) );
    LONGS_EQUAL(16777215, color(0xff, 0xff, 0xff));
}

TEST(StripAnimate, c)
{
	ws2801_setup(10,4,3); // leds length, data_pin, clock_pin;
	set_pixel_color(0, color(0,0,1));
	set_pixel_color(9, color(0,0,2));
	strip_show();
	LONGS_EQUAL(color(0,0,1), pixels[0]);
	LONGS_EQUAL(color(0,0,2), pixels[9]);
	free_strip();
}

TEST(StripAnimate, b)
{
	ws2801_setup(10,4,3);
	LONGS_EQUAL(0, pixels[0]);
	rgb_step(color(0,0,0));
	free_strip();
}
*/
