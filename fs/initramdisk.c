#include <fs/initramdisk.h>

initrd_header_t *initrd_header;
initrd_file_header_t *file_headers;

filesystem_node_t *initrd_root;
filesystem_node_t *initrd_dev;
filesystem_node_t *root_nodes;

int32_t number_of_root_nodes;

struct Dirent dirent;

static uint32_t initramdisk_read(filesystem_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer)
{
    initrd_file_header_t header = file_headers[node->inode];

    if(offset > header.length)  
        return 0;

    if(offset + size > header.length)
        size = header.length - offset;

    memcpy(buffer, (uint8_t*)(header.offset + offset), size);
    return size;
}

static struct Dirent *initramdisk_readdir(filesystem_node_t *node, uint32_t index)
{
    if(index - 1 > number_of_root_nodes)
        return 0;

    if(node == initrd_root && index == 0)
    {
        strcpy(dirent.name, "dev");
        dirent.name[3] = 0;
        dirent.ino = 0;
        return &dirent;
    }

    strcpy(dirent.name, root_nodes[index - 1].name);
    dirent.name[strlen(root_nodes[index - 1].name)] = 0;
    dirent.ino = root_nodes[index - 1].inode;
    return &dirent;
}

static filesystem_node_t *initramdisk_finddir(filesystem_node_t *node, char *name)
{
    if(node == initrd_root && !strcmp(name, "dev"))
        return initrd_dev;

    for(int32_t i = 0; i < number_of_root_nodes; ++i)
    {
        if(!strcmp(name, root_nodes[i].name))
            return &root_nodes[i];
    }

    return 0;
}

filesystem_node_t *init_initial_ram_disk(uint32_t location)
{
    // Init main and header fie pointers
    initrd_header = (initrd_header_t *) location;
    file_headers = (initrd_file_header_t *) (location + sizeof(initrd_header_t));

    // Init root directory
    initrd_root = (filesystem_node_t *) malloc(sizeof(filesystem_node_t));
    strcpy(initrd_root->name, "initrd");
    initrd_root->mask = 0;
    initrd_root->uid = 0;
    initrd_root->gid = 0;
    initrd_root->inode = 0;
    initrd_root->length = 0;
    initrd_root->flags = FS_DIRECTORY;
    initrd_root->read = 0;
    initrd_root->write = 0;
    initrd_root->open = 0;
    initrd_root->close = 0;
    initrd_root->readdir = &initramdisk_readdir;
    initrd_root->finddir = &initramdisk_finddir;
    initrd_root->ptr = 0;
    initrd_root->impl = 0;

    initrd_dev = (filesystem_node_t *) malloc(sizeof(filesystem_node_t));
    strcpy(initrd_dev->name, "dev");
    initrd_dev->mask = 0;
    initrd_dev->uid = 0;
    initrd_dev->gid = 0;
    initrd_dev->inode = 0;
    initrd_dev->length = 0;
    initrd_dev->flags = FS_DIRECTORY;
    initrd_dev->read = 0;
    initrd_dev->write = 0;
    initrd_dev->open = 0;
    initrd_dev->close = 0;
    initrd_dev->readdir = &initramdisk_readdir;
    initrd_dev->finddir = &initramdisk_finddir;
    initrd_dev->ptr = 0;
    initrd_dev->impl = 0;

    root_nodes = (filesystem_node_t *) malloc(sizeof(filesystem_node_t *) * initrd_header->number_of_files);
    number_of_root_nodes = initrd_header->number_of_files;

    for(int32_t i = 0; i < initrd_header->number_of_files; ++i)
    {
        file_headers[i].offset += location;
        strcpy(root_nodes[i].name, &file_headers[i].name);
        root_nodes[i].mask = 0;
        root_nodes[i].uid = 0; 
        root_nodes[i].gid = 0;
        root_nodes[i].length = file_headers[i].length;
        root_nodes[i].inode = i;
        root_nodes[i].flags = FS_FILE;
        root_nodes[i].read = &initramdisk_read;
        root_nodes[i].write = 0;
        root_nodes[i].readdir = 0;
        root_nodes[i].finddir = 0;
        root_nodes[i].open = 0;
        root_nodes[i].close = 0;
        root_nodes[i].impl = 0;
    }

    return initrd_root;
}