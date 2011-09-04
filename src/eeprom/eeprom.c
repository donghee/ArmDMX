#include "eeprom.h"

#define OUT 1
#define START_CONDITION 0
#define STOP_CONDITION 1

#define ACK_OK 0
#define ACK_ERROR 1

EEPROM* EEPROM_new(uint16_t i2c_address, uint8_t data_pin, uint8_t clock_pin)
{
    EEPROM* self = (EEPROM*) malloc(sizeof(EEPROM));
    self->address = i2c_address;
    self->data_pin = data_pin;
    self->clock_pin = clock_pin;

    pinMode(data_pin, OUT);
    pinMode(clock_pin, OUT);

    return self;
}

/*  */
/* void write_bit(EEPROM* self, uint8_t bit) */
/* { */
/* 	digitalWrite(self->clock_pin, HIGH); */
/* 	digitalWrite(self->data_pin, bit); */
/* 	digitalWrite(self->clock_pin, LOW); */
/* } */
/*  */

void start_bit(EEPROM* self)
{
	digitalWrite(self->data_pin, HIGH);
	digitalWrite(self->clock_pin, HIGH);
    /* delayus(1); */
	digitalWrite(self->data_pin, LOW);
	digitalWrite(self->clock_pin, LOW);
}

void stop_bit(EEPROM* self)
{
	digitalWrite(self->data_pin, LOW);
	digitalWrite(self->clock_pin, HIGH);
    /* delayus(1); */
	digitalWrite(self->data_pin, HIGH);
}


void write_byte(EEPROM* self, uint8_t byte)
{
    uint8_t i;
    for (i=0b10000000; i>0; i>>=1) 
    {
	    digitalWrite(self->clock_pin, HIGH);
        delayus(1);
	    digitalWrite(self->clock_pin, LOW);
        if (byte & i)
            digitalWrite(self->data_pin, HIGH);
        else 
            digitalWrite(self->data_pin, LOW);
    }
}


uint8_t read_byte(EEPROM* self)
{
    uint8_t i;
    uint8_t value;
    for (i=0b10000000; i>0; i>>=1) 
    {
	    digitalWrite(self->clock_pin, HIGH);
        delayus(1);
	    digitalWrite(self->clock_pin, LOW);
        if (digitalRead(self->data_pin) == HIGH)
            value |= i;
    }
    return value;
}

uint8_t receive_ack(EEPROM* self)
{
    digitalWrite(self->clock_pin, HIGH);
    if (digitalRead(self->data_pin) == LOW)
    {
        digitalWrite(self->clock_pin, LOW);
        return ACK_OK;
    }
    else {
        digitalWrite(self->clock_pin, LOW);
        return ACK_ERROR;
    }
}

void wait_ack(EEPROM* self)
{
    while(receive_ack(self) == ACK_ERROR) {};
}


void EEPROM_write_byte(EEPROM* self, uint16_t address, uint8_t data)
{
    uint8_t write_control_byte = 0x50;  //* if a[0-2] is GND with write operation, control byte is 0x50 */

    start_bit(self);
    
    write_byte(self, write_control_byte);
    wait_ack(self);
    
    write_byte(self, (address) >> 8);
    wait_ack(self);

    write_byte(self, (address) & 0xff);
    wait_ack(self);

    write_byte(self, data);
    wait_ack(self);

    stop_bit(self);
}


uint8_t EEPROM_read_byte(EEPROM* self, uint16_t address)
{
    // send to stop condition
    // send to start condition
    //

    uint8_t write_control_byte = 0x50;  /* if a[0-2] is GND with write operation, control byte is 0x50 */
    uint8_t read_control_byte = 0x51;  /* if a[0-2] is GND with read operation, control byte is 0x51 */

    uint8_t data;

    ///// write address
    /* stop_bit(self); */
    start_bit(self);

    write_byte(self, write_control_byte);
    wait_ack(self);

    write_byte(self, (address) >> 8);
    wait_ack(self);

    write_byte(self, (address) & 0xff);
    wait_ack(self);

    ////// read current address
    start_bit(self);

    write_byte(self, read_control_byte);
    wait_ack(self);

    data = read_byte(self);
    /* NO ACK */

    stop_bit(self);

    return data;
}

void EEPROM_free(EEPROM* self)
{
    free(self);
}
