#ifndef LUMAOS_GUI_BUTTON_H_
#define LUMAOS_GUI_BUTTON_H_

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <ltk/widget.h>
#include <ltk/wm.h>
#include <ltk/draw.h>

typedef struct Button
{
    widget_t widget;
    char *text;
    bool is_clicked;
    void (*on_click)();
    void (*on_release)();
} button_t;

button_t *new_button(char *text);
void button_on_draw(button_t *button, fb_t fb);
void button_set_on_click(button_t *button, void (*callback)(button_t*));
void button_set_text(button_t *button, const char *text);

#endif