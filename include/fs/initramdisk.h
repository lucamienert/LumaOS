#ifndef LUMAOS_INITRAMDISK_H_
#define LUMAOS_INITRAMDISK_H_

#pragma once

#include "filesystem.h"
#include "../libc/stdint.h"
#include "../libc/string.h"
#include "../kernel/memory.h"

typedef struct
{
    uint32 number_of_files;
} initrd_header_t;

typedef struct
{
    uint8   magic;
    int8    name[64];
    uint32  offset;
    uint32  length;
} initrd_file_header_t;

filesystem_node_t *init_initial_ram_disk(uint32 location);

#endif