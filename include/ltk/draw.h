#ifndef LUMAOS_DRAW_H_
#define LUMAOS_DRAW_H_

#pragma once

#include <stdint.h>
#include <gui/wm.h>

uint32_t *pixel_offset(fb_t fb, uint32_t x, uint32_t y);

void draw_pixel(fb_t fb, int32_t x, int32_t y, uint32_t col);
void draw_rect(fb_t fb, int32_t x, int32_t y, int32_t width, int32_t height, uint32_t col);
void draw_line(fb_t fb, int32_t x, int32_t y, int32_t x2, int32_t y2, uint32_t col);
void draw_char(fb_t fb, char c, int32_t x, int32_t y, uint32_t col);
void draw_string(fb_t fb, char *str, int32_t x, int32_t y, uint32_t col);
void draw_border(fb_t fb, int32_t x, int32_t y, int32_t width, int32_t height, uint32_t col);
void draw_rgb(fb_t fb, uint8_t *rgb, int32_t x, int32_t y, int32_t width, int32_t height);
void draw_rgba(fb_t fb, uint32_t *rgb, int32_t x, int32_t y, int32_t width, int32_t height);
void draw_rgb_masked(fb_t fb, uint8_t *rgb, int32_t x, int32_t y, int32_t width, int32_t height, uint32_t mask);

#endif