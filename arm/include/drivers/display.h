#ifndef LUMAOS_ARM_DISPLAY_H_
#define LUMAOS_ARM_DISPLAY_H_

#pragma once

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#define KERNEL_INFO 0
#define KERNEL_ERROR 1

struct Display
{
    void (*putc)(char c);
    uint8_t flags;
    char *name;
};

struct Display create(void (*putc)(char c), uint8_t flags, char *name);
void display_init(struct Display *display);
void print_tty(char *str, ...);

#endif