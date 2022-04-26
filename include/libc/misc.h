#ifndef LUMAOS_MISC_H_
#define LUMAOS_MISC_H_

#pragma once

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PACKED __attribute__((packed))

#define CLI() __asm__ volatile("cli")
#define STI() __asm__ volatile("sti")
#define HLT() __asm__ volatile("hlt")

#define low_16(address) \
    (unsigned short int)((address) & 0xFFFF)

#define high_16(address) \
    (unsigned short int)(((address) >> 16) & 0xFFFF)

#define low_8(address) \
    (uint8)((address) & 0xFF)

#define high_8(address) \
    (uint8)(((address) >> 8) & 0xFF)

#ifdef __cplusplus
}
#endif

#endif