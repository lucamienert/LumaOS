// http://www.jamesmolloy.co.uk/tutorial_html/8.-The%20VFS%20and%20the%20initrd.html
#ifndef LUMAOS_FILESYSTEM_H_
#define LUMAOS_FILESYSTEM_H_

#pragma once

#include "../utils/types.h"

#define MAX_FILENAME 128

#define FS_FILE        0x01
#define FS_DIRECTORY   0x02
#define FS_CHARDEVICE  0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE        0x05
#define FS_SYMLINK     0x06
#define FS_MOUNTPOINT  0x08

struct Filesystem_Node;

struct Dirent
{
    char name[MAX_FILENAME];
    uint32 ino;
};

typedef uint32 (*read_type_t)(struct Filesystem_Node*, uint32, uint32, uint8*);
typedef uint32 (*write_type_t)(struct Filesystem_Node*, uint32, uint32, uint8*);
typedef void (*open_type_t)(struct Filesystem_Node*);
typedef void (*close_type_t)(struct Filesystem_Node*);
typedef char* (*readdir_type_t)(struct Filesystem_Node*, uint32);
typedef struct Filesystem_Node* (*finddir_type_t)(struct Filesystem_Node*, char *name);

typedef struct Filesystem_Node
{
    char name[MAX_FILENAME];
    uint32 mask;
    uint32 uid;
    uint32 gid;
    uint32 flags;
    uint32 inode;
    uint32 length;
    uint32 impl;

    read_type_t read;
    write_type_t write;
    open_type_t open;
    close_type_t close;
    readdir_type_t readdir;
    finddir_type_t finddir;

    struct Filesystem_Node *link;
} filesystem_node_t;

extern filesystem_node_t *filesystem_root;

uint32 read_filesystem(filesystem_node_t *node, uint32 offset, uint32 size, uint8 *buffer);
uint32 write_filesystem(filesystem_node_t *node, uint32 offset, uint32 size, uint8 *buffer);
void open_filesystem(filesystem_node_t *node);
void close_filesystem(filesystem_node_t *node);
struct Dirent *read_directory(filesystem_node_t *node, uint32 index);
filesystem_node_t *find_directory(filesystem_node_t *node, char *name);

#endif