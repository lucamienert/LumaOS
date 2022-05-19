#include <ds/stack.h>

stack_t *stack_init(int32_t capacity)
{
    stack_t *stack = (stack_t*) malloc(sizeof(struct Stack));
    stack->maxsize = capacity;
    stack->top = -1;
    stack->items = (int32_t*) malloc(sizeof(int32_t) * capacity);

    return stack; 
}

int32_t stack_size(stack_t *stack)
{
    return stack->top + 1;
}

bool stack_empty(stack_t *stack)
{
    return stack->top == -1;
}

void stack_push(stack_t *stack, int32_t item)
{
    stack->items[++stack->top] = x;
}

int32_t stack_pop(stack_t *stack)
{
    if(stack_empty(stack))
        return;

    return stack->items[stack->top--];
}

int32_t stack_peek(stack_t *stack)
{
    if(stack_empty(stack))
        return;

    return stack->items[stack->top];
}