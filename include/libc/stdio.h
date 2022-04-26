#ifndef LUMAOS_STDIO_H_
#define LUMAOS_STDIO_H_

#pragma once

#include "stdint.h"
#include "misc.h"

#include "../drivers/display.h"

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

extern void panic(const char *message, const char *file, uint32 line);
extern void panic_assert(const char *file, uint32 line, const char *desc);

void printf(char *str);

#endif