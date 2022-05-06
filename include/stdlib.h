#ifndef LUMAOS_STDLIB_H_
#define LUMAOS_STDLIB_H_

#pragma once

#include <stdint.h>

void memcpy(void *source, void *dest, size_t nbytes);
void memset(void *dst, uint8_t value, size_t nbytes);

#endif