#ifndef LUMAOS_WINDOW_H_
#define LUMAOS_WINDOW_H_

#pragma once

typedef struct Window
{
    char *title;
    uint32_t width;
    uint32_t height;
    uint32_t id;
    uint32_t flags;
} window_t;

window_t *window_init(const char *title, uint32_t width, uint32_t height, uint32_t flags);
void window_close(window_t *window);
void window_draw(window_t *window);
void window_render(window_t *window);

#endif