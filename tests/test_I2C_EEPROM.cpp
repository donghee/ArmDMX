#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
//#include "WS2801.h"
#include "eeprom.h"
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

TEST(I2C_EEPROM, EEPROM_new)
{
    uint8_t i2c_address = 0x0000;
    EEPROM* e = EEPROM_new(i2c_address, 5,6);    
    LONGS_EQUAL(0x0, e->address);
    LONGS_EQUAL(5, e->data_pin);
    LONGS_EQUAL(6, e->clock_pin);
    EEPROM_free(e);
}


TEST(I2C_EEPROM, EEPROM_write_byte)
{
    uint16_t i2c_address = 0x0000; // 0x0000 ~ 0x7fff

    EEPROM* e = EEPROM_new(i2c_address, 5,6);    
    EEPROM_write_byte(e,i2c_address,0);
    //LONGS_EQUAL(0, 0);
    EEPROM_free(e);
}

TEST(I2C_EEPROM, EEPROM_read_byte)
{
    uint16_t i2c_address = 0x0000; // 0x0000 ~ 0x7fff
    uint8_t data;

    EEPROM* e = EEPROM_new(i2c_address, 5,6);    
    EEPROM_write_byte(e,i2c_address,1);
    data = EEPROM_read_byte(e,i2c_address);
    LONGS_EQUAL(0, data);
    EEPROM_free(e);
}
