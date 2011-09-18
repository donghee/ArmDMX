#ifndef ___SWITCH_H
#define ___SWITCH_H

#include "HardwareUtils.h"

uint8_t encode_rotary_switch(uint8_t code1, uint8_t code2, uint8_t code4, uint8_t
                           code8);
uint8_t read_rotary_switch(uint8_t* ports, uint8_t* pins);

uint8_t get_dmx_channel(void);

#endif

