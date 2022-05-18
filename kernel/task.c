#include <kernel/task.h>

volatile task_t *current_task;
volatile task_t *ready_queue;

extern page_directory_t *kernel_directory;
extern page_directory_t *current_directory;

extern void alloc_frame(page_t *, int32_t, int32_t);
extern uint32_t initial_esp;
extern uint32_t read_epi();

uint32_t next_pid = 1;

void init_taskmanager()
{
    CLI();

    move_stack((void *) 0xE0000000, 0x2000);

    current_task = ready_queue = (task_t *) kmalloc(sizeof(task_t));
    current_task->id = ++next_pid;
    current_task->esp = 0;
    current_task->ebp = 0;
    current_task->eip = 0;
    current_task->page_directory = current_directory;
    current_task->next = 0;
    current_task->kernel_stack = kmalloc_a(STACK_SIZE);

    STI();
}

void task_switch()
{
    if (!current_task)
        return;

    uint32_t esp, ebp, eip;
    asm volatile("mov %%esp, %0" : "=r"(esp));
    asm volatile("mov %%ebp, %0" : "=r"(ebp));

    eip = read_eip();

    if (eip == 0x12345)
        return;

    current_task->eip = eip;
    current_task->esp = esp;
    current_task->ebp = ebp;
    
    current_task = current_task->next;
    if (!current_task) current_task = ready_queue;

    eip = current_task->eip;
    esp = current_task->esp;
    ebp = current_task->ebp;

    current_directory = current_task->page_directory;

    setup();

    asm volatile("\
        cli;\
        mov %0, %%ecx;\
        mov %1, %%esp;\
        mov %2, %%ebp;\
        mov %3, %%cr3;\
        mov $0x12345, %%eax;\
        sti;\
        jmp *%%ecx" : : "r"(eip), "r"(esp), "r"(ebp), "r"(current_directory->physicalAddr)
    );
}

int32_t task_fork()
{
    asm volatile("cli");

    task_t *parent_task = (task_t*) current_task;

    page_directory_t *directory = clone_directory(current_directory);

    task_t *new_task = (task_t*) kmalloc(sizeof(task_t));
    new_task->id = next_pid++;
    new_task->esp = new_task->ebp = 0;
    new_task->eip = 0;
    new_task->page_directory = directory;
    current_task->kernel_stack = kmalloc_a(STACK_SIZE);
    new_task->next = 0;

    task_t *tmp_task = (task_t*)ready_queue;
    while (tmp_task->next)
        tmp_task = tmp_task->next;

    tmp_task->next = new_task;

    uint32_t eip = read_eip();

    if (current_task != parent_task)
        return 0;

    uint32_t esp; asm volatile("mov %%esp, %0" : "=r"(esp));
    uint32_t ebp; asm volatile("mov %%ebp, %0" : "=r"(ebp));
    new_task->esp = esp;
    new_task->ebp = ebp;
    new_task->eip = eip;

    STI();

    return new_task->id;
}

void move_stack(void *new_stack_start, uint32_t size)
{
    for(uint32_t i = (uint32_t) new_stack_start; i >= ((uint32_t) new_stack_start - size); i -= 0x1000)
        alloc_frame(get_page(i, 1, current_directory), 0, 1);

    uint32_t page_directory_address;

    asm volatile("mov %%cr3, %0" : "=r" (page_directory_address));
    asm volatile("mov %0, %%cr3" : : "r" (page_directory_address));

    uint32_t old_stack_pointer; 
    asm volatile("mov %%esp, %0" : "=r" (old_stack_pointer));
    
    uint32_t old_base_pointer;  
    asm volatile("mov %%ebp, %0" : "=r" (old_base_pointer));
    
    uint32_t offset = (uint32_t)new_stack_start - initial_esp;
    
    uint32_t new_stack_pointer = old_stack_pointer + offset;
    uint32_t new_base_pointer = old_base_pointer + offset;
    
    memcpy((void*) new_stack_pointer, (void*) old_stack_pointer, initial_esp-old_stack_pointer);
    
    for(uint32_t i = (uint32_t) new_stack_start; i > (uint32_t) new_stack_start-size; i -= 4)
    {
        uint32_t tmp = *(uint32_t*) i;
        if (( old_stack_pointer < tmp) && (tmp < initial_esp))
        {
            tmp = tmp + offset;
            uint32_t *tmp2 = (uint32_t*)i;
            *tmp2 = tmp;
        }
    }

    asm volatile("mov %0, %%esp" : : "r" (new_stack_pointer));
    asm volatile("mov %0, %%ebp" : : "r" (new_base_pointer));
}

void setup()
{
    set_kernel_stack(current_task->kernel_stack + STACK_SIZE);
}

int32_t task_get_pid()
{
    return current_task->id;
}