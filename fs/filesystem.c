#include "../include/fs/filesystem.h"

filesystem_note_t *filesystem_root = 0;

uint32 read_filesystem(filesystem_node_t *node, uint32 offset, uint32 size, uint8 *buffer)
{
    return node->read != 0 ? node->read(node, offset, size, buffer) : 0;
}

uint32 write_filesystem(filesystem_node_t *node, uint32 offset, uint32 size, uint8 *buffer)
{
    return node->write != 0 ? node->write(node, offset, size, buffer) : 0;
}

void open_filesystem(filesystem_node_t *node)
{
    if(node->open != 0)
        return node->open(node);
}

void close_filesystem(filesystem_node_t *node)
{
    if(node->close != 0)
        return node->close(node);
}

struct Dirent *read_directory(filesystem_node_t *node, uint32 index)
{
    return (node->flags & 0x7) == FS_DIRECTORY && node->readdir != 0
        ? node->readdir(node, index);
        : 0
}

filesystem_node_t *find_directory(filesystem_node_t *node, char *name)
{
    return (node->flags & 0x7) == FS_DIRECTORY && node->finddir != 0
        ? node->finddir(node, index);
        : 0
}