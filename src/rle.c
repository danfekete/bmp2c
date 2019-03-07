#include "rle.h"

void RLE_Init(RLE *rle)
{
    rle->buffer = (RLETYPE *)malloc(sizeof(RLETYPE) * STARTSIZE);
    rle->size = STARTSIZE;
    rle->used = 0;
    rle->lastValue = NULL;
    rle->currentCounter = 0;
    rle->closed = 0;
}

void RLE_Deinit(RLE *rle)
{
    free(rle->buffer);
    rle->buffer = NULL;
    rle->size = rle->used = 0;
}

void _RLE_AddToArray(RLE *rle, RLETYPE value)
{
    if(rle->used >= rle->size) {
        // buffer overflow, resize the array to allow it to have more items
        rle->size += STARTSIZE;
        rle->buffer = (RLETYPE *)realloc(rle->buffer, sizeof(RLETYPE) * rle->size);
    }
    rle->buffer[rle->used++] = value;
}

void _RLE_FlushToArray(RLE *rle)
{
    if(rle->currentCounter == 0) return;

    uint8_t compressed = rle->currentCounter << 1;
    if(rle->lastValue > 0) compressed |= 0x01;
    _RLE_AddToArray(rle, compressed);
    //_RLE_AddToArray(rle, rle->currentCounter);
    //_RLE_AddToArray(rle, rle->lastValue);
    //printf("\n");
    rle->currentCounter = 0;
    rle->lastValue = NULL;
}

void RLE_PushValue(RLE *rle, RLETYPE value)
{
    if(value != rle->lastValue || rle->currentCounter == 127) 
    {
        _RLE_FlushToArray(rle);
        rle->lastValue = value;
        rle->currentCounter = 1;
    } else 
    {
        if(rle->currentCounter == 0) 
        {
            rle->lastValue = value;
        }
        rle->currentCounter++;
    }
}

void RLE_Finish(RLE *rle)
{
    rle->buffer = (RLETYPE*)realloc(rle->buffer, rle->used);
    rle->size = rle->used;
    rle->currentCounter = 0;
    rle->lastValue = NULL;
    rle->closed = 1;
}

void RLE_FromMono(RLE *rle, MONOBUFFER *buffer)
{
    for(int i=0;i<buffer->width*buffer->height;i++) 
    {
        uint8_t v = (uint8_t)(buffer->buffer[i] * 255);
        RLE_PushValue(rle, v);
    }
}

 void RLE_Write(RLE *rle, FILE *out)
 {
     // Always close the RLE before writing!
    if(rle->closed == 0) RLE_Finish(rle);
    fwrite(rle->buffer, sizeof(RLETYPE), rle->size, out);
 }
