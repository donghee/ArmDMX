#ifndef ___SWITCH_H__
#define ___SWITCH_H__

#include "HardwareGpio.h"

uint8_t read_rotary_switch(uint8_t code1, uint8_t code2, uint8_t code4, uint8_t
                           code8);

uint8_t get_channel(void);

#endif

