#ifndef ___WS2801_UTILS_H__
#define ___WS2801_UTILS_H__

#include "LPC11xx.h"
#include "WS2801.h"


uint8_t channels;

void rainbow(uint8_t wait);

struct strip* make_strips(uint8_t channels, uint16_t led_size);

void set_color(struct strip* self, uint16_t pixel, uint32_t color);

void show(struct strip* strips);

void set_data_clock_pin(struct strip* self, uint8_t data_pin, uint8_t clock_pin);

void free_strips(struct strip* strips);

#endif

