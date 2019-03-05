#if !defined(_BMP_H)
#define _BMP_H

#include <stdio.h>
#include <stdint.h>
#include "buffer.h"

#pragma pack(push, 1)
typedef struct _BMP_FileStruct
{
    uint16_t magic;
    uint32_t size;
    uint16_t reserved[2];
    uint32_t offset;
} BMP_FileStruct;
#pragma pack(pop)

COLORBUFFER* BMP_ReadBitmap(const char* fname);

#endif // _BMP_H
