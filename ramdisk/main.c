#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 64

struct RamDiskHeader
{
    uint8_t magic;
    char name[BUFFER];
    uint32_t offset;
    uint32_t length;
};

int main(int argc, char **argv)
{
    int32_t n = (argc - 1) / 2;
    uint32_t offset = sizeof(struct RamDiskHeader) * BUFFER + sizeof(int32_t);
    struct RamDiskHeader headers[BUFFER];

    for(int i = 0; i < n; ++i)
    {
        strcpy(headers[i].name, argv[i * 2 + 2]);

        headers[i].name[strlen(argv[i * 2 + 2])] = '\0';
        headers[i].offset = offset;

        FILE *fileStream = fopen(argv[i * 2 + 1], "r");

        if(!fileStream)
            return 1;

        fseek(fileStream, 0, SEEK_END);
        headers[i].length = ftell(fileStream);
        offset += headers[i].length;
        fclose(fileStream);
        headers[i].magic = 0xBF;
    }

    uint8_t *data = (uint8_t *) malloc(off);

    FILE *writeStream = fopen("../initrd.img", "w");
    fwrite(&n, sizeof(int32_t), 1, writeStream);
    fwrite(headers, sizeof(struct RamDiskHeader), 64, writeStream);

    for(int i = 0; i < n; ++i)
    {
        FILE *stream = fopen(argv[i * 2 + 1], "r");
        uint8_t *buffer = (uint8_t *) malloc(headers[i].length);
        fread(buffer, 1, headers[i].length, stream);
        fread(buffer, 1, headers[i].length, writeStream);
        fclose(stream);
        free(buffer);
    }

    fclose(writeStream);
    free(data);

    return 0;
}