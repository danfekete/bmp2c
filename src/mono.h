#if !defined(_MONO_H)
#define _MONO_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "buffer.h"

typedef struct {

    uint32_t width, height;
    float *buffer;

} MONOBUFFER;

void MONO_Init(MONOBUFFER *mono, uint32_t width, uint32_t height);
void MONO_Deinit(MONOBUFFER *mono);
void MONO_FromBuffer(MONOBUFFER *mono, COLORBUFFER *buffer);

void MONO_Threshold(MONOBUFFER *mono, float threshold);
float MONO_GetXY(MONOBUFFER *mono, uint32_t x, uint32_t y);
void MONO_SetXY(MONOBUFFER *mono, uint32_t x, uint32_t y, float value);
void MONO_FloydSteinberg(MONOBUFFER *mono, float threshold);

void MONO_FlushPPM(MONOBUFFER *mono, FILE *out);

#endif // _MONO_H
