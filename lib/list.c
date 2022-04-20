#include "../include/lib/list.h"

list_t *init_list(int64 item_size)
{
    list_t *list = (list_t*) malloc(sizeof(struct LIST_STRUCT));
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