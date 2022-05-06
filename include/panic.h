#ifndef LUMAOS_PANIC_H_
#define LUMAOS_PANIC_H_

#pragma once

#include <asm/system.h>

#define PANIC(msg) panic(msg, __FILE__, __LINE__);

extern void panic(const char *message, const char *file, uint32_t line);
extern void panic_assert(const char *file, uint32_t line, const char *desc);

#endif