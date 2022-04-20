#include "../include/kernel/taskmanager.h"

struct Task create_task(void entrypoint())
{
    struct Task task;
    task.cpuState = (struct CPUState*)(task.stack + STACK_SIZE - sizeof(struct CPUState));

    task.cpuState->eax = 0;
    task.cpuState->ebx = 0;
    task.cpuState->ecx = 0;
    task.cpuState->edx = 0;    
    task.cpuState->esi = 0;
    task.cpuState->edi = 0;
    task.cpuState->ebp = 0;

    task.cpuState->eip = (unsigned long int) entrypoint;
    task.cpuState->eflags = 0x202;

    return task;
}

struct TaskManager create_taskmanager()
{
    struct TaskManager manager;
    manager.numTasks = 0;
    manager.currentTask = -1;
    return manager;
}

int8 add_task(struct TaskManager taskManager, struct Task *task)
{
    if(taskManager.numTasks >= 256)
        return 0;

    taskManager.tasks[taskManager.numTasks++] = task;
    return 1;
}

struct CPUState *schedule(struct TaskManager taskManager, struct CPUState *cpuState)
{
    if(taskManager.numTasks <= 0)
        return cpuState;

    if(taskManager.currentTask >= 0)
        taskManager.tasks[taskManager.currentTask]->cpuState = cpuState;

    if(++taskManager.currentTask >= taskManager.numTasks)
        taskManager.currentTask %= taskManager.numTasks;

    return taskManager.tasks[taskManager.currentTask]->cpuState;
}