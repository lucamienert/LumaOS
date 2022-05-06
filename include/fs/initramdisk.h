#ifndef LUMAOS_INITRAMDISK_H_
#define LUMAOS_INITRAMDISK_H_

#pragma once

#include <fs/filesystem.h>

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    uint32_t number_of_files;
} initrd_header_t;

typedef struct
{
    uint8_t magic;
    int8_t name[64];
    uint32_t offset;
    uint32_t length;
} initrd_file_header_t;

filesystem_node_t *init_initial_ram_disk(uint32_t location);

#endif