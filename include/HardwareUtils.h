#ifndef __HARDWARE_UTILS_H
#define __HARDWARE_UTILS_H

#include "LPC11xx.h"

#define HIGH 1
#define LOW 0

#define ON 1
#define OFF 0

#define IN 0
#define OUT 1

extern void (*pinMode)(uint8_t, uint8_t);
extern void (*digitalPortPinWrite)(uint8_t, uint8_t, uint8_t);
extern void (*digitalWrite)(uint8_t,uint8_t);
extern uint8_t (*digitalPortPinRead)(uint8_t, uint8_t);
extern uint8_t (*digitalRead)(uint8_t);
extern void (*delayms)(uint32_t);
extern void (*delayus)(uint32_t);

#endif
