#include "draw.h"

void DRAW_Init(DRAW *draw, void (*drawFunc)(uint16_t x, uint16_t y, uint32_t color))
{
    draw->drawFunc = drawFunc;
}

void DRAW_CompressedBitmap(DRAW *draw, uint8_t *data, uint32_t len, uint16_t width, uint16_t height)
{
    // Every byte, the first 7 bits are the count (how many times the color is repeated) 
    // and the last bit is the color (BLACK = 0 or WHITE = 1)
    uint32_t pixelCounter = 0;
    for(uint32_t i = 0; i < len; i++) 
    {
        uint8_t counter = data[i] >> 1;
        uint8_t color = data[i] & 0x01;
        
        while(counter-- > 0) 
        {
            pixelCounter++;
            uint16_t x = pixelCounter % width;
            uint16_t y = (pixelCounter - x) / width;
            draw->drawFunc(x, y, color);
        }
        
    }
}