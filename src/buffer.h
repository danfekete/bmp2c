#if !defined(_BUFFER_H)
#define _BUFFER_H

#include <stdint.h> 
#include <stdlib.h>
#include "color.h"

typedef struct _COLOR_BUFFER
{

    uint32_t size;
    COLORDATA *buffer;
    uint32_t nextPos;

} COLORBUFFER;

void BUFFER_Init(COLORBUFFER *buffer, uint32_t size);
void BUFFER_Deinit(COLORBUFFER *buffer);
int BUFFER_AddColor(COLORBUFFER *buffer, COLORDATA *data);
void BUFFER_Grayscale(COLORBUFFER *buffer);

// File operations
void BUFFER_FlushBinary(COLORBUFFER *buffer, FILE *out);

#endif // _BUFFER_H
