#include "include/list.h"

list_t *init_list(int64_t item_size)
{
    list_t *list = (list_t*) malloc(sizeof(struct List));
    list->size = 0;
    list->item_size = item_size;
    list->items = 0;
    return list;
}

void list_append(list_t *list, void *item)
{
    list->size++;

    if(list->items)
        list->items = realloc(list->items, (list->size * list->item_size));
        
    list->items = malloc(list->item_size);
    list->items[list->size - 1] = item;
}

void delete_list(list_t *list)
{
    free(list->items);
    free(list);
}