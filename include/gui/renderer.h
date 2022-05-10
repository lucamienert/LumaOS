#ifndef LUMAOS_RENDERER_H_
#define LUMAOS_RENDERER_H_

#pragma once

#include <stdint.h>

#define FRAME_BUFFER_0 320
#define FRAME_BUFFER_1 200

struct Pixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

typedef struct Renderer
{
    struct Pixel frameBuffer[FRAME_BUFFER_0][FRAME_BUFFER_1];
} renderer_t;

renderer_t *init_renderer();

#endif
