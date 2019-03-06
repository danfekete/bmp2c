#include "buffer.h"

void BUFFER_Init(COLORBUFFER *buffer, uint32_t size, uint32_t width, uint32_t height)
{
    buffer->size = size;
    buffer->buffer = (COLORDATA*)malloc(sizeof(COLORDATA)*size);
    buffer->nextPos = 0;
    buffer->width = width;
    buffer->height = height;
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
    fwrite(buffer->buffer, sizeof(COLORDATA), buffer->size, out);
}

void BUFFER_FlushPPM(COLORBUFFER *buffer, FILE *out)
{
    // Write magic
    fprintf(out, "P3\n%d %d\n255\n", buffer->width, buffer->height);
    //printf("PIXELS: %d\n", buffer->size);
    for(int i=0;i<buffer->size;i++) 
    {
        //fwrite(&buffer->buffer[i], sizeof(COLORDATA), 1, out);
        COLORDATA* curr = &buffer->buffer[i];
        fprintf(out, "%d %d %d", curr->r, curr->g, curr->b);
        if(i % buffer->width == 0 && i > 0) fprintf(out, "\n");
        else fprintf(out, "\t");
    }
}