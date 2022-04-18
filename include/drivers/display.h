#ifndef LMOS_DISPLAY_H_
#define LMOS_DISPLAY_H_

#pragma once

#include "../utils/inttypes.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 50
#define MAX_COLS 160
#define WHITE_ON_BLACK 0x0f

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void print(char *str);
void print_nl();
void clear_screen();
int8 scroll_ln(int8 offset);
void print_backspace();

#endif