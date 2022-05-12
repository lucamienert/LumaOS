#ifndef LUMAOS_LIST_H_
#define LUMAOS_LIST_H_

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* LINKED LIST */
typedef struct List
{
    void **items;
    size_t size;
    size_t item_size;
} list_t;

list_t *list_init(int64_t item_size);
void list_append(list_t *list, void *item);
void list_delete(list_t *list);

/* ORDERED LIST */
typedef int8_t (*lessthan_predicate_t)(type_t, type_t);

typedef struct OrderedList
{
    type_t *array;
    uint32_t size;
    uint32_t max_size;
    lessthan_predicate_t less_than;
} ordered_list_t;

ordered_list_t ordered_list_init(uint32_t max_size, lessthan_predicate_t less_than);
ordered_list_t ordered_list_place(void *addr, uint32_t max_size, lessthan_predicate_t less_than);
void ordered_list_destroy(ordered_list_t *list);
void ordered_list_insert(type_t item, ordered_list_t *list);
type_t ordered_list_get(uint32_t index, ordered_list_t *list);
void orderer_list_destroy_at(uint32_t index, ordered_list_t *list);

#ifdef __cplusplus
}
#endif

#endif