#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "WS2801.h"
#include "utils.h"

#include "LPC11xx.h"
#include "FakeHardwareGpio.h"
}

TEST_GROUP(WS2801)
{


    static void mock_pinMode(uint8_t pin, uint8_t mode) {
        mock().actualCall("pinMode").
            withParameter("pin", pin).
            withParameter("mode", mode);
    }

    static void mock_digitalWrite(uint8_t pin, uint8_t bitVal) {
        mock().actualCall("digitalWrite").
            withParameter("pin", pin).
            withParameter("bitVal", bitVal);
    }
    
	void setup()
    {
        UT_PTR_SET(pinMode, &mock_pinMode);
        UT_PTR_SET(digitalWrite, &mock_digitalWrite);        
    }
    void teardown()
    {
    }
};

void mock_expect_pinMode(int pin1, int pin2, int value)
{
    mock().expectOneCall("pinMode").withParameter("pin", pin1).withParameter("mode",value);
    mock().expectOneCall("pinMode").withParameter("pin", pin2).withParameter("mode",value);
}

TEST(WS2801, color)
{
    LONGS_EQUAL(0, color(0x00, 0x00,0x00) );
    LONGS_EQUAL(16777215, color(0xff, 0xff, 0xff));
}

TEST(WS2801, Strip_new_free)
{
    mock_expect_pinMode(3,4,1);

	uint16_t led_size = 100;
    Strip* strip = Strip_new(led_size, 3, 4);
    
	uint16_t i;
	for (i=0;i<100;i++)
	{
		LONGS_EQUAL(0, strip->pixels[i]);
	}
    Strip_free(strip);
}

TEST(WS2801, Strip_setPixel)
{
    mock_expect_pinMode(3,4,1);
    
    uint16_t led_size = 10;
    Strip* strip = Strip_new(led_size, 3,4);
    Strip_setPixel(strip, 0, color(0,0,1));
    LONGS_EQUAL(color(0,0,1), strip->pixels[0]);

    Strip_setPixel(strip, 9, color(0xff,0xff,0xff));
    LONGS_EQUAL(color(0xff,0xff,0xff), strip->pixels[9]);

    Strip_free(strip);
}

TEST(WS2801, Strip_show)
{
    int data_pin = 3;
    int clock_pin = 4;
    uint16_t led_size = 10;
    
    UT_PTR_SET(pinMode, &Fake_pinMode);                   
    UT_PTR_SET(digitalWrite, &Fake_digitalWrite);               

    Strip* strip = Strip_new(led_size, data_pin,clock_pin);
    Strip_setPixel(strip, 0, color(0,0,1));
    Strip_setPixel(strip, 9, color(0xff,0xff,0xff));

    Strip_show(strip);
    Strip_free(strip);
}

TEST(WS2801, Strip_rgb_setup)
{
    int data_pin = 3;
    int clock_pin = 4;
    
    UT_PTR_SET(pinMode, &Fake_pinMode);
    
    int i;
    for (i=0b100000000000000000000000; i>0; i>>=1)
        {
            mock().expectOneCall("digitalWrite").withParameter("pin",
                                                               clock_pin).withParameter("bitVal",LOW);
            mock().expectOneCall("digitalWrite").withParameter("pin",
                                                               data_pin).withParameter("bitVal",LOW);
            mock().expectOneCall("digitalWrite").withParameter("pin",
                                                               clock_pin).withParameter("bitVal",HIGH);
        }
    rgb_step(color(0,0,0),data_pin, clock_pin);
}

TEST(WS2801, utils_wheel)
{
	LONGS_EQUAL(color(0,0xff,0), wheel(0));
	LONGS_EQUAL(color(0xff,0,0), wheel(85));
	LONGS_EQUAL(color(0,0xff,0), wheel(255));
}

TEST(WS2801, utils_rainbow)
{
    UT_PTR_SET(pinMode, &Fake_pinMode);    
    UT_PTR_SET(digitalWrite, &Fake_digitalWrite);
    
    uint16_t led_size = 10;
    Strip* strip = Strip_new(led_size, 3,4);    
    rainbow(strip, 100); //delay is 100 ms
    Strip_free(strip);
}

TEST(WS2801, Four_Strips) {
    UT_PTR_SET(pinMode, &Fake_pinMode);    
    UT_PTR_SET(digitalWrite, &Fake_digitalWrite);

    uint8_t i;
	uint16_t led_size = 100;
    Strip* strip1 = Strip_new(led_size, 3,4);
    Strip* strip2 = Strip_new(led_size, 5,6);
    Strip* strip3 = Strip_new(led_size, 7,8);        
    Strip* strip4 = Strip_new(led_size+2, 9,10);

    LONGS_EQUAL(3, strip1->data_pin);
    LONGS_EQUAL(4, strip1->clock_pin);

    for(i=0; i< 100; i++) {
        LONGS_EQUAL(0, strip1->pixels[i]);
    }
    
    LONGS_EQUAL(5, strip2->data_pin);
    LONGS_EQUAL(6, strip2->clock_pin);

    LONGS_EQUAL(7, strip3->data_pin);
    LONGS_EQUAL(8, strip3->clock_pin);

    LONGS_EQUAL(9, strip4->data_pin);
    LONGS_EQUAL(10, strip4->clock_pin);


    Strip_setPixel(strip1, 0, color(0,0,1));
    LONGS_EQUAL(color(0,0,1), strip1->pixels[0]);

    Strip_setPixel(strip2, 0, color(0xff,0xff,0xff));
    LONGS_EQUAL(color(0xff,0xff,0xff), strip2->pixels[0]);

    Strip_setPixel(strip3, 99, color(0xff,0x00,0xff));
    LONGS_EQUAL(color(0xff,0x00,0xff), strip3->pixels[99]);

    Strip_setPixel(strip4, 101, color(0xf0,0x00,0xff));
    LONGS_EQUAL(color(0xf0,0x00,0xff), strip4->pixels[101]);
    
    Strip_free(strip1);
    Strip_free(strip2);
    Strip_free(strip3);
    Strip_free(strip4);        
}
