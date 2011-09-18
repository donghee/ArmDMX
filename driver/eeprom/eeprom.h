#ifndef ___EEPROM_H__
#define ___EEPROM_H__

#include "HardwareUtils.h"

#include <stdlib.h>
#include "LPC11xx.h"

typedef struct
{
	uint8_t data_pin; /* SDA */
	uint8_t clock_pin; /* SCL */
    uint16_t address;
} EEPROM;

EEPROM* EEPROM_new(uint16_t device_address, uint8_t data_pin, uint8_t clock_pin);
void EEPROM_write_byte(EEPROM* self, uint16_t address, uint8_t data);
uint8_t EEPROM_read_byte(EEPROM* self, uint16_t address);
void EEPROM_free(EEPROM* self);
#endif
