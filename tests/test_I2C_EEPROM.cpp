#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
//#include "WS2801.h"
//#include "LPC11xx.h"
//#include "gpio.h"
}

TEST_GROUP(I2C_EEPROM)
{
	void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(I2C_EEPROM, a)
{
    LONGS_EQUAL(0, 0);
    LONGS_EQUAL(0, 1);
}
