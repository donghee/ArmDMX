#ifndef __HARDWARE_UTILS_H
#define __HARDWARE_UTILS_H

#include "LPC11xx.h"

#define HIGH 1
#define LOW 0

#define ON 1
#define OFF 0

#define IN 0
#define OUT 1

extern void (*GPIOSetDir)(uint8_t, uint8_t, uint8_t) ;
extern void (*delay32Us)(uint8_t, uint32_t);
extern void (*delay32Ms)(uint8_t, uint32_t);

#endif
