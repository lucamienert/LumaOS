#ifndef LUMAOS_RENDERER_H_
#define LUMAOS_RENDERER_H_

#pragma once

struct Pixel
{
    uint8 r;
    uint8 g;
    uint8 b;
};

typedef struct Renderer
{
    struct Pixel frameBuffer[320][200];
} renderer_t;

renderer_t *init_renderer();

#endif