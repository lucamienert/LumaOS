#ifndef LUMAOS_DISPLAY_H_
#define LUMAOS_DISPLAY_H_

#pragma once

#include <stdint.h>

#define VIDEO_ADDRESS 0xb8000

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

enum
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GRAY,
    GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    WHITE
};

void display_put(char c);
void display_print(char *str);
void display_clear();
void display_backspace();

#endif