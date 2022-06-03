#ifndef LUMAOS_SYSINFO_H_
#define LUMAOS_SYSINFO_H_

#pragma once

#include <stdint.h>
#include <stdfloat.h>

#define KERNEL_VERSION "0.0.2"

#define SYSINFO_UPTIME 1
#define SYSINFO_MEMORY 2
#define SYSINFO_LOG    4

typedef struct SysBuffer
{
    uint8_t *buf;
    uint32_t size;
} sysbuffer_t;

typedef struct SysInfo
{
    uint32_t kernel_heap_usage;
    uint32_t ram_usage;
    uint32_t ram_total;
    float64_t uptime;
    char *kernel_log;
} sysinfo_t;

#endif
