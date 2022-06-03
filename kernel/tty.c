#include <kernel/tty.h>
#include <system/sysinfo.h>
#include <fs/filesystem.h>
#include <string.h>

void init_tty(filesystem_node_t *node)
{
    char dir[MAX_FILENAME] = node->name;
    printf("LumaOS [%s]> ", dir);
}

void execute_command(char *command)
{
    if(strcmp(command, "version") == 0)
    {
        printf("Current Kernel Version: %s", KERNEL_VERSION);
    }
}
