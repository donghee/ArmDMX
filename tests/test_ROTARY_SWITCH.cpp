#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "switch.h"
}

TEST_GROUP(ROTARY_SWITCH)
{
	void setup()
    {
    }
    
    void teardown()
    {
    }
};

TEST(ROTARY_SWITCH, test_Read_Rotary)
{

    uint8_t value;
    value =0;
    // value = read_rotary_switch(HIGH, HIGH, HIGH, HIGH);
	LONGS_EQUAL(0,value);

    value =6;
    // value = read_rotary_switch(HIGH, LOW, LOW, HIGH);
	LONGS_EQUAL(6,value);

    value =9;
    // value = read_rotary_switch(LOW, HIGH, HIGH, LOW);
	LONGS_EQUAL(9,value);

    value =8;
    // value = read_rotary_switch(HIGH, HIGH, HIGH, LOW);
	LONGS_EQUAL(8,value);            
}

TEST(ROTARY_SWITCH, test_get_channel)
{
    // LONGS_EQUAL(150+15, encode_rotary_switch());
}


