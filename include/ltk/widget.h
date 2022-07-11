#ifndef LUMAOS_WIDGET_H_
#define LUMAOS_WIDGET_H_

#pragma once

#include <stdint.h>

#include <ltk/inc.h>
#include <ltk/window.h>
#include <ltk/wm.h>

#define WIDGET(x) ((widget_t *) x)

#define EXPAND_VERTICAL 1
#define EXPAND_HORIZONTAL 2
#define EXPAND  (EXPAND_VERTICAL | EXPAND_HORIZONTAL)

#define DEFAULT_PADDING 8

typedef struct Rect
{
    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;
} rect_t;

typedef struct ColorScheme
{
    uint64_t background_color;
    uint64_t base_color;
    uint64_t border_color;
    uint64_t text_color;
    uint64_t highlight;
    uint64_t border_color2;
} colorscheme_t;

typedef struct Widget
{
    struct Widget *parent;
    colorscheme_t color;
    rect_t bounds;

    uint32_t flags;

    void *data;

    void (*on_click)(struct Widget *, point_t);
    void (*on_mouse_release)(struct Widget *, point_t);
    void (*on_mouse_move)(struct Widget *, point_t);
    void (*on_mouse_enter)(struct Widget *, point_t);
    void (*on_mouse_exit)(struct Widget *);
    void (*on_draw)(struct Widget *, fb_t);
    void (*on_free)(struct Widget *);
    void (*on_resize)(struct Widget *);
} widget_t;

typedef void (*widget_clicked_t)(widget_t *, point_t);
typedef void (*widget_mouse_moved_t)(widget_t *, point_t);
typedef void (*widget_mouse_entered_t)(widget_t *, point_t);
typedef void (*widget_mouse_exited_t)(widget_t *);
typedef void (*widget_mouse_release_t)(widget_t *, point_t);
typedef void (*widget_draw_t)(widget_t *, fb_t);
typedef void (*widget_resize_t)(widget_t *);
typedef void (*widget_freed_t)(widget_t *);

typedef struct UIRoot
{
    window_t *window;
    widget_t *root;
} ui_root_t;

#endif