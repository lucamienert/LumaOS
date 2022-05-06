#ifndef LUMAOS_MISC_H_
#define LUMAOS_MISC_H_

#pragma once

#define low_16(address) \
    (unsigned short int)((address) & 0xFFFF)

#define high_16(address) \
    (unsigned short int)(((address) >> 16) & 0xFFFF)

#define low_8(address) \
    (unsigned char)((address) & 0xFF)

#define high_8(address) \
    (unsigned char)(((address) >> 8) & 0xFF)

#endif