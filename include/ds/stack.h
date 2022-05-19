#ifndef LUMAOS_STACK_H_
#define LUMAOS_STACK_H_

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Stack
{
    int32_t maxsize;
    int32_t top;
    int32_t *items;
} stack_t;

stack_t *stack_init(int32_t capacity);
int32_t stack_size(stack_t *stack);
bool stack_empty(stack_t *stack);
void stack_push(stack_t *stack, int32_t item);
int32_t stack_pop(stack_t *stack);
int32_t stack_peek(stack_t *stack);

#endif