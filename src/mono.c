#include "mono.h"

void MONO_Init(MONOBUFFER *mono, uint32_t width, uint32_t height)
{
    mono->width = width;
    mono->height = height;
    mono->buffer = (double *)malloc(sizeof(double) * width * height);
}

void MONO_Deinit(MONOBUFFER *mono)
{
    free(mono->buffer);
    free(mono);
}

void MONO_FromBuffer(MONOBUFFER *mono, COLORBUFFER *buffer)
{
    for(int i=0; i<buffer->size; i++)
    {
        // use the red channel, and convert to double
        // since most of the dithering works on doubles
        mono->buffer[i] = (double)(buffer->buffer[i].r) / 255.0; // use the red channel
    }
}

inline double MONO_GetXY(MONOBUFFER *mono, uint32_t x, uint32_t y)
{
    if(x >= mono->width || x < 0 || y < 0 || y >= mono->height) return 0;
    return mono->buffer[x + mono->width * y];
}

inline void MONO_SetXY(MONOBUFFER *mono, uint32_t x, uint32_t y, double value)
{
    if (x >= mono->width || x < 0 || y < 0 || y >= mono->height) return;
    mono->buffer[x + mono->width * y] = CLAMP(0.0, 1.0, value);
}

void MONO_Threshold(MONOBUFFER *mono, double threshold)
{
    for (int i = 0; i < mono->width * mono->height; i++) 
    {
        mono->buffer[i] = mono->buffer[i] >= threshold ? 1.0 : 0.0;
    }
}

void MONO_FloydSteinberg(MONOBUFFER *mono, double threshold)
{
    for(int x=0; x<mono->width; x++) 
    {
        for(int y=0; y<mono->height;y++)
        {
            double oldpixel = MONO_GetXY(mono, x, y);
            double newpixel = oldpixel >= threshold ? 1.0 : 0.0;
            //double newpixel = round(oldpixel);
            double error = oldpixel - newpixel;
            //printf("%f %f %f\n", oldpixel, newpixel, error);
            MONO_SetXY(mono, x, y, newpixel);
            MONO_SetXY(mono, x + 1, y, MONO_GetXY(mono, x + 1, y) + (error * 0.4375));
            MONO_SetXY(mono, x - 1, y + 1, MONO_GetXY(mono, x - 1, y + 1) + (error * 0.1875));
            MONO_SetXY(mono, x, y + 1, MONO_GetXY(mono, x, y + 1) + (error * 0.3125));
            MONO_SetXY(mono, x + 1, y + 1, MONO_GetXY(mono, x + 1, y + 1) + (error * 0.0625));
        }
    }
}

void MONO_FlushPPM(MONOBUFFER *mono, FILE *out)
{
    fprintf(out, "P2\n%d %d\n255\n", mono->width, mono->height);
    
    uint32_t size = mono->width * mono->height;
    //printf("size: %d\n", size);
    for (int i = 0; i < size; i++)
    {
        fprintf(out, "%d ", (uint8_t)(mono->buffer[i] * 255.0));
        if (i % 76 == 0 && i > 0)
            fprintf(out, "\n");
    }
}