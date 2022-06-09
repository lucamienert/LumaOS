#include <kernel/memory/paging.h>
#include <kernel/memory/heap.h>

page_directory_t *kernel_directory = 0;
page_directory_t *current_directory = 0;

uint32_t *frames;
uint32_t number_of_frames;

extern uint32_t placement_address;
extern heap_t *heap;

static void set_frame(uint32_t frame_addr)
{
    uint32_t frame = frame_addr / 0x1000;
    uint32_t index = INDEX_FROM_BIT(frame);
    uint32_t offset = OFFSET_FROM_BIT(frame);
    frames[index] |= 0x1 << offset;
}

static void clear_frame(uint32_t frame_addr)
{
    uint32_t frame = frame_addr / 0x1000;
    uint32_t index = INDEX_FROM_BIT(frame);
    uint32_t offset = OFFSET_FROM_BIT(frame);
    frames[index] &= ~(0x1 << offset);
}

static uint32_t set_frame(uint32_t frame_addr)
{
    uint32_t frame = frame_addr / 0x1000;
    uint32_t index = INDEX_FROM_BIT(frame);
    uint32_t offset = OFFSET_FROM_BIT(frame);
    return (frames[index] & (0x1 << offset));
}

static uint32_t first_frame()
{
    for(uint32_t i = 0; i < INDEX_FROM_BIT(number_of_frames); ++i)
    {
        if(frames[i] != 0xFFFFF000)
        {
            for(uint32_t j = 0; j < 32; ++j)
            {
                uint32_t test = 0x1 << j;
                if(!(frames[i] & test))
                    return i * 4 * 8 + j;
            }
        }
    }
}

void alloc_frame(page_t *page,int32_t is_kernel, int32_t is_writable)
{
    if(page->frame != 0)
        return;

    uint32_t index = first_frame();
    if(index == (uint32_t) -1)
        PANIC("No free frames");

    set_frame(index * 0x1000);
    page->present = 1;
    page->rw = is_writable == 1 ? 1 : 0;
    page->user = is_kernel == 1 ? 1 : 0;
    page->frame = index;
}

void free_frame(page_t *page)
{
    uint32_t frame;
    if(!(frame = page->frame))
        return;

    clear_frame(frame);
    page->frame = 0x0;
}

void init_paging()
{
    uint32_t memory_end_page = 0x1000000;
    number_of_frames = memory_end_page / 0x1000;
    frames = (uint32_t*) kmalloc(INDEX_FROM_BIT(number_of_frames));
    memset(frames, 0, INDEX_FROM_BIT(number_of_frames));

    uint32_t phys;
    kernel_directory = (page_directory_t*) kmalloc_a(sizeof(page_directory_t));
    memset(kernel_directory, 0, sizeof(page_directory_t));
    kernel_directory->physicalAddr = (uint32_t) kernel_directory->tablesPhysical;

    for(int32_t i = HEAP_START; i < HEAP_START + HEAP_INITIAL_SIZE; i += 0x1000)
        get_page(i, 1, kernel_directory);

    int32_t i = 0;
    while(i < 0x400000)
    {
        alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
        i += 0x1000;
    }

    for (i = HEAP_START; i < HEAP_START + HEAP_INITIAL_SIZE; i += 0x1000)
        alloc_frame(get_page(i, 1, kernel_directory), 0, 0);

    register_interrput_handler(14, page_fault);
    switch_page_directory(kernel_directory);

    heap = create_heap(HEAP_START, HEAP_START + HEAP_INITIAL_SIZE, 0xCFFFF000, 0, 0);

    current_directory = clone_directory(kernel_directory);
    switch_page_directory(current_directory);
}

void switch_page_directory(page_directory_t *newDir)
{
    current_directory = newDir;
    asm volatile("mov %0, %%cr3":: "r"(newDir->physicalAddr));
    uint32_t cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page_t *get_page(uint32_t address, int32_t make, page_directory_t *dir)
{
    address /= 0x1000;
    uint32_t table_index = address / 1024;

    if (dir->tables[table_index])
        return &dir->tables[table_index]->pages[address%1024];
    else if(make)
    {
        uint32_t tmp;
        dir->tables[table_index] = (page_table_t*) kmalloc_ap(sizeof(page_table_t), &tmp);
        memset(dir->tables[table_index], 0, 0x1000);
        dir->tablesPhysical[table_index] = tmp | 0x7;
        return &dir->tables[table_index]->pages[address % 1024];
    }
    else return 0;
}

void page_fault(registers_t *regs)
{
    PANIC("Page fault");
}

static page_table_t *clone_table(page_table_t *src, uint32_t *physAddr)
{
    page_table_t *table = (page_table_t*) kmalloc_ap(sizeof(page_table_t), physAddr);
    memset(table, 0, sizeof(page_directory_t));

    for (int32_t i = 0; i < 1024; ++i)
    {
        if (!src->pages[i].frame)
            continue;

        alloc_frame(&table->pages[i], 0, 0);
        if(src->pages[i].present)
            table->pages[i].present = 1;
        if(src->pages[i].rw)
            table->pages[i].rw = 1;
        if(src->pages[i].user)
            table->pages[i].user = 1;
        if(src->pages[i].accessed)
            table->pages[i].accessed = 1;
        if(src->pages[i].dirty)
            table->pages[i].dirty = 1;

        copy_page_physical(src->pages[i].frame * 0x1000, table->pages[i].frame * 0x1000);
    }
    return table;
}

page_directory_t *clone_directory(page_directory_t *src)
{
    uint32_t phys;
    page_directory_t *dir = (page_directory_t*) kmalloc_ap(sizeof(page_directory_t), &phys);
    memset(dir, 0, sizeof(page_directory_t));

    uint32_t offset = (uint32_t) dir->tablesPhysical - (uint32_t)dir;
    dir->physicalAddr = phys + offset;

    for (int32_t i = 0; i < 1024; ++i)
    {
        if (!src->tables[i])
            continue;

        if (kernel_directory->tables[i] == src->tables[i])
        {
            dir->tables[i] = src->tables[i];
            dir->tablesPhysical[i] = src->tablesPhysical[i];
        }
        else
        {
            uint32_t phys;
            dir->tables[i] = clone_table(src->tables[i], &phys);
            dir->tablesPhysical[i] = phys | 0x07;
        }
    }
    return dir;
}