#include <list.h>

list_t *list_init(int64_t item_size)
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

void list_delete(list_t *list)
{
    free(list->items);
    free(list);
}

ordered_list_t ordered_list_init(uint32_t max_size, lessthan_predicate_t less_than)
{
    ordered_list_t list;
}

ordered_list_t ordered_list_place(void *addr, uint32_t max_size, lessthan_predicate_t less_than)
{
    ordered_list_t list;
}

void ordered_list_destroy(ordered_list_t *list)
{

}

void ordered_list_insert(type_t item, ordered_list_t *list)
{

}

type_t ordered_list_get(uint32_t index, ordered_list_t *list)
{
    return list->array[index];
}

void orderer_list_destroy_at(uint32_t index, ordered_list_t *list)
{

}