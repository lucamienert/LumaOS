#ifndef LUMAOS_TASKMANAGER_H_
#define LUMAOS_TASKMANAGER_H_

#pragma once

#include "../libc/stdint.h"

#define STACK_SIZE 4096

struct CPUState
{
    uint32 eax;
    uint32 ebx;
    uint32 ecx;
    uint32 edx;

    uint32 esi;
    uint32 edi;
    uint32 ebp;
    uint32 error;

    uint32 eip;
    uint32 cs;
    uint32 eflags;
    uint32 esp;
    uint32 ss;
} __attribute__((packed));

struct Task
{
    uint8 stack[STACK_SIZE];
    struct CPUState *cpuState;
};

struct Task create_task(void entrypoint());

struct TaskManager
{
    struct Task *tasks[256];
    int32 numTasks;
    int32 currentTask;
};

struct TaskManager create_taskmanager();
int8 add_task(struct TaskManager taskManager, struct Task *task);
struct CPUState *schedule(struct TaskManager taskManager, struct CPUState *cpuState);

#endif