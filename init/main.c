#include <lumaos/kernel/kernel.h>
#include <system/multiboot.h>
#include <stdint.h>

void main(multiboot_header_t *multiboot_ptr, uint32_t initial_stack)
{
    kernel_main(initial_stack);
}