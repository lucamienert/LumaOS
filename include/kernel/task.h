#ifndef LUMAOS_TASK_H_
#define LUMAOS_TASK_H_

#pragma once

#include <stdint.h>

#define STACK_SIZE 4096

typedef struct Task
{
    int32_t id;
    uint32_t esp;
    uint32_t ebp;
    uint32_t eip;
    uint32_t kernel_stack;
    page_directory_t *page_directory;
    struct Task *next;
} task_t;

void init_taskmanager();
void task_switch();
int32_t task_fork();
void move_stack(void *new_stack_start, uint32_t size);
int32_t task_get_pid();

#endif