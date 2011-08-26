#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "WS2801.h"
#include "utils.h"

#include "LPC11xx.h"
#include "gpio.h"
}

TEST_GROUP(WS2801)
{
	void setup()
    {
    }
    void teardown()
    {
    }
};

TEST(WS2801, color)
{
    LONGS_EQUAL(0, color(0x00, 0x00,0x00) );
    LONGS_EQUAL(16777215, color(0xff, 0xff, 0xff));
}

TEST(WS2801, make_strip)
{
	uint16_t LEDS_SIZE = 100;
	make_strip(LEDS_SIZE);

	uint16_t i;
	for (i=0;i<100;i++)
	{
		LONGS_EQUAL(0, pixels[i]);
	}
	free_strip();
}


TEST(WS2801, set_pixel_color)
{
	// strip 사이즈보다 크면 지정 안함 안함
	make_strip(10);
	set_pixel_color(0, color(0,0,0));
	LONGS_EQUAL(0, pixels[0]);
	free_strip();

	make_strip(10);
	set_pixel_color(15, color(0,0,0));
	//NOT_EQUAL(0, pixels[15]);
	free_strip();
}

TEST(WS2801, ws2801_setup)
{
	ws2801_setup(10, 4, 3); // leds length, data_pin, clock_pin;
	LONGS_EQUAL(4, data_pin);
	LONGS_EQUAL(3, clock_pin);
	LONGS_EQUAL(0, pixels[0]);
	free_strip();
}

TEST(WS2801, strip_show)
{
	ws2801_setup(10,4,3); // leds length, data_pin, clock_pin;
	set_pixel_color(0, color(0,0,1));
	set_pixel_color(9, color(0,0,2));
	strip_show();
	LONGS_EQUAL(color(0,0,1), pixels[0]);
	LONGS_EQUAL(color(0,0,2), pixels[9]);
	free_strip();
}

//TEST(WS2801, get_graydata)
//{
//	LONGS_EQUAL(0xf0, get_graydata(color(0xf0, 0xf1, 0xf2), RED));
//	LONGS_EQUAL(0xf1, get_graydata(color(0xf0, 0xf1, 0xf2), GREEN));
//	LONGS_EQUAL(0xf2, get_graydata(color(0xf0, 0xf1, 0xf2), BLUE));
//}

TEST(WS2801, strip_one_step)
{
	ws2801_setup(10,4,3);
	LONGS_EQUAL(0, pixels[0]);
	rgb_step(color(0,0,0));
	free_strip();
}


TEST(WS2801, wheel)
{
	LONGS_EQUAL(color(0,0xff,0), wheel(0));
	LONGS_EQUAL(color(0xff,0,0), wheel(85));
	LONGS_EQUAL(color(0,0xff,0), wheel(255));
}

TEST(WS2801, utils_rainbow)
{
	ws2801_setup(10,4,3);
    // rainbow(100); //delay is 100 ms
	free_strip();
}

// mock usage: https://github.com/dh/EmbeddedTddWorkshop/blob/master/ChordedKeyboard/tests/test_keyboard.cpp
TEST(WS2801, make_strips)
{
	uint16_t led_size = 100;
    uint8_t channel_size =4;
    struct strip* strips;

	strips = make_strips(channel_size, led_size);

	set_data_clock_pin(&strips[0],3,4);
	set_data_clock_pin(&strips[1],5,6);
	set_data_clock_pin(&strips[2],7,8);
	set_data_clock_pin(&strips[3],9,10);

	LONGS_EQUAL(3, strips[0].data_pin);
	LONGS_EQUAL(4, strips[0].clock_pin);
	LONGS_EQUAL(5, strips[1].data_pin);
	LONGS_EQUAL(6, strips[1].clock_pin);
	LONGS_EQUAL(7, strips[2].data_pin);
	LONGS_EQUAL(8, strips[2].clock_pin);
	LONGS_EQUAL(9, strips[3].data_pin);
	LONGS_EQUAL(10, strips[3].clock_pin);

	uint16_t ch,i;
    for (ch =0; ch<4; ch++) {
        for (i=0;i<100;i++) {
            LONGS_EQUAL(0, strips[ch].pixels[i]);
        }
    }

    set_color(&strips[1],0,color(0,0,1));
    LONGS_EQUAL(color(0,0,1), strips[1].pixels[0]);

    set_color(&strips[1],99,color(0xff,0xff,0xff));
    LONGS_EQUAL(color(0xff,0xff,0xff), strips[1].pixels[99]);

    set_color(&strips[2],00,color(0xff,0xff,0x00));
    LONGS_EQUAL(color(0xff,0xff,0x00), strips[2].pixels[00]);

    set_color(&strips[3],99,color(0xff,0x00,0xff));
    LONGS_EQUAL(color(0xff,0x00,0xff), strips[3].pixels[99]);

    show(strips);

	free_strips(strips);
}


	// set_pixel_color(0, color(0,0,1));
	// set_pixel_color(9, color(0,0,2));
	// strip_show();

