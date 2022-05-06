#ifndef LUMAOS_FILESYSTEM_H_
#define LUMAOS_FILESYSTEM_H_

#pragma once

#include <stdint.h>

#define MAX_FILENAME 128

#define FS_FILE        0x01
#define FS_DIRECTORY   0x02
#define FS_CHARDEVICE  0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE        0x05
#define FS_SYMLINK     0x06
#define FS_MOUNTPOINT  0x08

struct FilesystemNode;

struct Dirent
{
    char name[MAX_FILENAME];
    uint32_t ino;
};

typedef uint32_t (*read_type_t)(struct FilesystemNode*, uint32_t, uint32_t, uint8_t*);
typedef uint32_t (*write_type_t)(struct FilesystemNode*, uint32_t, uint32_t, uint8_t*);
typedef void (*open_type_t)(struct FilesystemNode*);
typedef void (*close_type_t)(struct FilesystemNode*);
typedef char* (*readdir_type_t)(struct FilesystemNode*, uint32_t);
typedef struct FilesystemNode* (*finddir_type_t)(struct FilesystemNode*, char *name);

typedef struct FilesystemNode
{
    char name[MAX_FILENAME];
    uint32_t mask;
    uint32_t uid;
    uint32_t gid;
    uint32_t flags;
    uint32_t inode;
    uint32_t length;
    uint32_t impl;

    read_type_t read;
    write_type_t write;
    open_type_t open;
    close_type_t close;
    readdir_type_t readdir;
    finddir_type_t finddir;

    struct FilesystemNode *link;
} filesystem_node_t;

extern filesystem_node_t *filesystem_root;

uint32_t read_filesystem(filesystem_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);
uint32_t write_filesystem(filesystem_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);
void open_filesystem(filesystem_node_t *node);
void close_filesystem(filesystem_node_t *node);
struct Dirent *read_directory(filesystem_node_t *node, uint32_t index);
filesystem_node_t *find_directory(filesystem_node_t *node, char *name);

#endif