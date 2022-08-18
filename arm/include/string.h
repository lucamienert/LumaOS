#ifndef LUMAOS_ARM_STRING_H_
#define LUMAOS_ARM_KERNEL_H_

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int64_t strlen(const char *str);
void itoa(unsigned i, unsigned base, char *buf);

#ifdef __cplusplus
}
#endif

#endif