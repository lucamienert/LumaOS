#ifndef LUMAOS_LIST_H_
#define LUMAOS_LIST_H_

#pragma once

#include "../kernel/memory.h"
#include "../utils/types.h"

typedef struct LIST_STRUCT
{
    int32 size;
    int64 item_size;
    int64 items;
} list_t;

list_t *init_list(int64 item_size);
void list_append(list_t *list, void *item);

#endif