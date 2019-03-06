#if !defined(_BUFFER_H)
#define _BUFFER_H
#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include "color.h"

typedef struct _COLOR_BUFFER
{
    uint32_t width, height;
    uint32_t size;
    COLORDATA *buffer;
    uint32_t nextPos;

} COLORBUFFER;

void BUFFER_Init(COLORBUFFER *buffer, uint32_t size, uint32_t width, uint32_t height);
void BUFFER_Deinit(COLORBUFFER *buffer);
int BUFFER_AddColor(COLORBUFFER *buffer, COLORDATA *data);
void BUFFER_Grayscale(COLORBUFFER *buffer);

// File operations
void BUFFER_FlushBinary(COLORBUFFER *buffer, FILE *out);
void BUFFER_FlushPPM(COLORBUFFER* buffer, FILE *out);

#endif // _BUFFER_H
