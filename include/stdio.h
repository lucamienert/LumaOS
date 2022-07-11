#ifndef LUMAOS_STDIO_H_
#define LUMAOS_STDIO_H_

#pragma once

#include <stdint.h>

typedef struct
{
    int32_t df;
    char *name;
} FILE;

extern FILE *stdout;
extern FILE *stderr;

#ifdef __cplusplus
extern "C" {
#endif

void printf(char *str);

#ifdef __cplusplus
}
#endif

#endif