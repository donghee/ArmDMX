#include "switch.h"

uint8_t D0_PORT[] = { 1, 1, 1, 1 };
uint8_t D0_PIN[] = { 1, 2, 4, 5 };

uint8_t D1_PORT[] = { 0, 0, 0, 1 };
uint8_t D1_PIN[] = { 8, 9, 11, 0 };

uint8_t D2_PORT[] = { 0, 0, 0, 0 };
uint8_t D2_PIN[] = { 2, 3, 6, 7 };

uint8_t read_rotary_switch(uint8_t code1, uint8_t code2, uint8_t code4, uint8_t code8)
{
    return (!code8 << 3) | (!code4 << 2) | (!code2 << 1) | (!code1 );
}

uint8_t read_rotary_switch2(uint8_t* ports, uint8_t* pins)
{
	int i;
	uint8_t code1 = digitalPortPinRead(ports[0], pins[0]);
	uint8_t code2 = digitalPortPinRead(ports[1], pins[1]);
	uint8_t code4 = digitalPortPinRead(ports[2], pins[2]);
	uint8_t code8 = digitalPortPinRead(ports[3], pins[3]);

	return read_rotary_switch(code1, code2, code4, code8);

}
uint8_t get_channel()
{
    int i=0;
    int ch_one_digit;
    int ch_two_digit;    
    int ch_three_digit;
    
    // set rotary switch pin mode IN
    for (i=0; i < 4; i++) {
        pinMode(D0_PIN[i], IN);
    }
    for (i=0; i < 4; i++) {
        pinMode(D1_PIN[i], IN);
    }
    for (i=0; i < 4; i++) {
        pinMode(D2_PIN[i], IN);
    }

    ch_one_digit = read_rotary_switch2(D0_PORT, D0_PIN);
    ch_two_digit = read_rotary_switch2(D1_PORT, D1_PIN);
    ch_three_digit = read_rotary_switch2(D2_PORT, D2_PIN);

    if (ch_three_digit > 6) {
        ch_three_digit = 0; // TOFIX If ch_three over 6, raise error.
    }

    return ch_three_digit * 100 + ch_two_digit* 10 + ch_one_digit;
}
