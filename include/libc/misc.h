#ifndef LUMAOS_MISC_H_
#define LUMAOS_MISC_H_

#pragma once

#define PACKED __attribute__((packed))

#define CLI() __asm__ volatile("cli")
#define STI() __asm__ volatile("sti")
#define HLT() __asm__ volatile("hlt")

#define low_16(address) \
    (unsigned short int)((address) & 0xFFFF)

#define high_16(address) \
    (unsigned short int)(((address) >> 16) & 0xFFFF)

#endif