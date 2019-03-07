#if !defined(_RLE_H)
#define _RLE_H

#include <stdint.h>
#include <stdlib.h>
#include "mono.h"

#define STARTSIZE 1024

typedef uint8_t RLETYPE;

typedef struct {
    RLETYPE *buffer;
    uint32_t size;
    uint32_t used;
    RLETYPE lastValue;
    uint8_t currentCounter;
    char closed;
} RLE;

void RLE_Init(RLE* rle);
void RLE_Deinit(RLE *rle);
void RLE_FromMono(RLE *rle, MONOBUFFER *buffer);

// internal function
void _RLE_AddToArray(RLE *rle, RLETYPE value);
void _RLE_FlushToArray(RLE *rle);

// push values
void RLE_PushValue(RLE *rle, RLETYPE value);
// Finish the RLE encoding process
void RLE_Finish(RLE *rle);
void RLE_Write(RLE *rle, FILE *out);

#endif // _RLE_H
