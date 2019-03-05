#include "buffer.h"
#include <stdio.h>

void BUFFER_Init(COLORBUFFER *buffer, uint32_t size)
{
    buffer->size = size;
    buffer->buffer = (COLORDATA*)malloc(sizeof(COLORDATA)*size);
    buffer->nextPos = 0;
}

void BUFFER_Deinit(COLORBUFFER *buffer)
{
    free(buffer->buffer);
    free(buffer);
}

int BUFFER_AddColor(COLORBUFFER *buffer, COLORDATA *data)
{
    if(buffer->nextPos > buffer->size) return NULL;
    buffer->buffer[buffer->nextPos] = *data;
    buffer->nextPos++;
    return 1;
}

void BUFFER_Grayscale(COLORBUFFER *buffer)
{
    for(int i=0;i<buffer->size;i++) 
    {
        COLOR_ToGrayscale(&buffer->buffer[i]);
    }
}

void BUFFER_FlushBinary(COLORBUFFER *buffer, FILE *out)
{
    fwrite(buffer->buffer, sizeof(COLORDATA), buffer->size, stdout);
}