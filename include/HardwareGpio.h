#ifndef __HARDWARE_GPIO_H__
#define __HARDWARE_GPIO_H__

#include "LPC11xx.h"

#define HIGH 1
#define LOW 0

extern void (*pinMode)(uint8_t, uint8_t);
extern void (*digitalWrite)(uint8_t, uint8_t);
extern void (*delayms)(uint32_t);
extern void (*delayus)(uint32_t);

#endif
