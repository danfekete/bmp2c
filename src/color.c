#include "color.h"

void COLOR_ToGrayscale(COLORDATA *color)
{
    // From: http://poynton.ca/notes/colour_and_gamma/ColorFAQ.html
    uint8_t mono = (0.2125f * color->r) + (0.7154f * color->g) + (0.0721f * color->b);
    color->r = mono;
    color->g = mono;
    color->b = mono;
}

uint8_t COLOR_ToSingleChannelGraycale(COLORDATA *color)
{
    COLOR_ToGrayscale(color);
    return color->r;
}

uint8_t COLOR_ToMonochrome(COLORDATA *color, uint8_t threshold)
{
    uint8_t grayScale = COLOR_ToSingleChannelGraycale(color);
    return grayScale >= threshold ? 0xFF : 0x00;
}