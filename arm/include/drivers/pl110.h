#ifndef LUMAOS_ARM_PL110_H_
#define LUMAOS_ARM_PL110_H_

#pragma once

#include <stdint.h>
#include <font.h>

#include <drivers/display.h>

#define PL110_CR_EN   0x001
#define PL110_CR_PWR  0x800
#define PL110_IOBASE  0xc0000000
#define PL110_PALBASE (PL110_IOBASE + 0x200)

struct PL110
{
    uint32_t volatile tim0;
    uint32_t volatile tim1;
    uint32_t volatile tim2;
    uint32_t volatile d;
    uint32_t volatile upbase;
    uint32_t volatile f;
    uint32_t volatile g;
    uint32_t volatile control;
};

void pl110_put_pixel(uint32_t x, uint32_t y, uint32_t color);
void pl110_put(char c);
void pl110_init();

#endif