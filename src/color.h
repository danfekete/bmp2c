#if !defined(_COLOR_H)
#define _COLOR_H

#include <stdint.h>

#pragma pack(push, 1)
typedef struct _COLORDATA
{
    uint8_t b, g, r;
} COLORDATA;
#pragma pack(pop)

void COLOR_ToGrayscale(COLORDATA *color);
uint8_t COLOR_ToSingleChannelGraycale(COLORDATA *color);
uint8_t COLOR_ToMonochrome(COLORDATA *color, uint8_t threshold);


#endif // _COLOR_H
