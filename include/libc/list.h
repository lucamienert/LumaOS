#ifndef LUMAOS_LIST_H_
#define LUMAOS_LIST_H_

#pragma once

#include "stdint.h"
#include "stdlib.h"

typedef struct List
{
    void **items;
    size_t size;
    size_t item_size;
} list_t;

list_t *init_list(int64 item_size);
void list_append(list_t *list, void *item);
void delete_list(list_t *list);

#endif