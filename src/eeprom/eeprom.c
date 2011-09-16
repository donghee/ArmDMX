#include "eeprom.h"

#define OUT 1
#define IN 0

#define START_CONDITION 0
#define STOP_CONDITION 1

#define ACK_OK 0
#define ACK_ERROR 1

#define i2c_timing 50

EEPROM* EEPROM_new(uint16_t device_address, uint8_t data_pin, uint8_t clock_pin)
{
    EEPROM* self = (EEPROM*) malloc(sizeof(EEPROM));
    self->address = device_address;
    self->data_pin = data_pin;
    self->clock_pin = clock_pin;

    pinMode(data_pin, OUT);
    pinMode(data_pin, IN);

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
	digitalWrite(self->clock_pin, LOW);
	delayus(i2c_timing);

	digitalWrite(self->data_pin, HIGH);
	delayus(i2c_timing);
	digitalWrite(self->clock_pin, HIGH);
	delayus(i2c_timing);
    /* delayus(1); */
	digitalWrite(self->data_pin, LOW);
	delayus(i2c_timing);
	digitalWrite(self->clock_pin, LOW);
	delayus(i2c_timing);
}

void stop_bit(EEPROM* self)
{
	digitalWrite(self->clock_pin, LOW);
	delayus(i2c_timing);
	digitalWrite(self->data_pin, LOW);
	delayus(i2c_timing);
	digitalWrite(self->clock_pin, HIGH);
	delayus(i2c_timing);
    /* delayus(1); */
	digitalWrite(self->data_pin, HIGH);
	delayus(i2c_timing);
}


void write_byte(EEPROM* self, uint8_t byte)
{
    uint8_t i;
    for (i=0b10000000; i>0; i>>=1) 
    {
	    digitalWrite(self->clock_pin, HIGH);
        delayus(i2c_timing);
	    digitalWrite(self->clock_pin, LOW);
        delayus(i2c_timing);
        if (byte & i)
            digitalWrite(self->data_pin, HIGH);
        else 
            digitalWrite(self->data_pin, LOW);
        delayus(i2c_timing);

    }
}


uint8_t read_byte(EEPROM* self)
{
    uint8_t i;
    uint8_t value;
    uint8_t tmp; // TO DEBUG
    for (i=0b10000000; i>0; i>>=1) 
    {
	    digitalWrite(self->clock_pin, HIGH);
        delayus(i2c_timing);
	    digitalWrite(self->clock_pin, LOW);
        delayus(i2c_timing);
        tmp=digitalRead(self->data_pin);
        if (tmp == HIGH)
            value |= i;
        delayus(i2c_timing);
    }
    return value;
}

uint8_t receive_ack(EEPROM* self)
{
    uint8_t ack;
	digitalWrite(self->clock_pin, HIGH);
	delayus(i2c_timing);
    ack = digitalRead(self->data_pin);
    if (ack == LOW)
    {
        digitalWrite(self->clock_pin, LOW);
        delayus(i2c_timing);
        return ACK_OK;
    }
    else {
        digitalWrite(self->clock_pin, LOW);
        delayus(i2c_timing);
        return ACK_ERROR;
    }
}

void wait_ack(EEPROM* self)
{
    //while(receive_ack(self) == ACK_ERROR) {};
    digitalWrite(self->data_pin, HIGH);
    delayus(i2c_timing);
	digitalWrite(self->clock_pin, HIGH);
	delayus(i2c_timing);
    digitalWrite(self->clock_pin, LOW);
	delayus(i2c_timing);
}


void EEPROM_write_byte(EEPROM* self, uint16_t mem_address, uint8_t data)
{

    start_bit(self);
    
    write_byte(self, self->address << 1 );
    wait_ack(self);
    write_byte(self, ((mem_address) >> 8) & 0xff);
    wait_ack(self);
    write_byte(self, (mem_address) & 0xff);
    wait_ack(self);

    write_byte(self, data);
    wait_ack(self);

    stop_bit(self);

    delayms(25); // allow for the programming of the eeprom
}


uint8_t EEPROM_read_byte(EEPROM* self, uint16_t mem_address)
{
    uint8_t data;

    ///// write address
    /* stop_bit(self); */
    start_bit(self);

    write_byte(self, self->address << 1);
    wait_ack(self);
    write_byte(self, ((mem_address) >> 8) & 0xff);
    wait_ack(self);
    write_byte(self, (mem_address) & 0xff);
    wait_ack(self);

    ////// read current address
    start_bit(self);

    write_byte(self, (self->address << 1) | 1);
    wait_ack(self);

    data = read_byte(self);
    /* NO ACK */
    stop_bit(self);

    return data;
}

//void EEPROM_write_page(EEPROM* self, )
//void i2c_eeprom_write_page( int deviceaddress, unsigned int eeaddresspage, byte* data, byte length ) {
//http://pastebin.com/f3a36644b

void EEPROM_free(EEPROM* self)
{
    free(self);
}
