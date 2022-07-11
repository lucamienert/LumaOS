#ifndef LUMAOS_WINDOW_MANAGER_H_
#define LUMAOS_WINDOW_MANAGER_H_

#pragma once

#include <ltk/inc.h>

typedef struct FB
{
    uint64_t address;
    uint32_t pitch;
    uint32_t width;
    uint32_t height;
    uint32_t bpp;
} fb_t;

#endif