#if !defined(_DRAW_H)
#define _DRAW_H

#include <stdint.h>

typedef struct 
{
    void (*drawFunc)(uint16_t x, uint16_t y, uint32_t color);
} DRAW;

void DRAW_Init(DRAW *draw, void (*drawFunc)(uint16_t x, uint16_t y, uint32_t color));
void DRAW_CompressedBitmap(DRAW *draw, uint8_t *data, uint32_t len, uint16_t width, uint16_t height);

#endif // _DRAW_H
