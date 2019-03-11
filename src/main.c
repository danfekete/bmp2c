#include <stdio.h>
#include <string.h>
#include "bmp.h"
#include "mono.h"
#include "rle.h"
#include "h_writer.h"
#include "draw.h"
#include "../argparse/argparse.h"

static const char *const usage[] = {
    "bmp2c [options] filename",
    NULL,
};

const uint16_t width = 128;
const uint16_t height = 64;
unsigned char *displayBuffer;

void draw(uint16_t x, uint16_t y, uint32_t color)
{
    displayBuffer[x + width * y] = color > 0x00 ? 'x' : ' ';
}

void outputDisplayBuffer()
{
    printf("\n");
    for(int i=0;i<width*height;i++)
    {
        printf("%c", displayBuffer[i]);
        if(i % width == 0 && i > 0) printf("\n");
    }
    printf("\n");
}

int main(int argc, char **argv) 
{
    float dither = 0.5;
    const char *path = NULL;
    const unsigned char floyd;
    const unsigned char test;

    uint32_t imageWidth, imageHeight;

    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_STRING('o', "output", &path, "Output"),
        OPT_FLOAT('d', "dither", &dither, "Dither threshold"),
        OPT_BOOLEAN('f', 'floyd', &floyd, "Use Floyd-Steinberg algorithm to dither"),
        OPT_BOOLEAN('t', 'test', &test, 'Test the dithered image'),
        OPT_END()
    };

    struct argparse argparse;
    argparse_init(&argparse, options, usage, 0);
    argc = argparse_parse(&argparse, argc, argv);

    if(argc < 1) 
    {
        printf("No bitmap added!\n");
        exit(-1);
    }
    COLORBUFFER *buf =  BMP_ReadBitmap(argv[0]);
    MONOBUFFER *mono = (MONOBUFFER*)malloc(sizeof(MONOBUFFER));
    RLE *rle = (RLE*)malloc(sizeof(RLE));
    
    imageWidth = buf->width;
    imageHeight = buf->height;

    BUFFER_Grayscale(buf);
    MONO_Init(mono, buf->width, buf->height);
    MONO_FromBuffer(mono, buf);
    BUFFER_Deinit(buf); // kill the buffer
    
    if(floyd)
    {
        MONO_FloydSteinberg(mono, dither);
    }
    
    MONO_Threshold(mono, dither);
    
    RLE_Init(rle);
    RLE_FromMono(rle, mono);
    RLE_Finish(rle);
    
    MONO_Deinit(mono); // Kill mono
    
    FILE *f;
    if(path)
    {
        f = fopen(path, "w");
    }
    else
    {
        f = stdout;
    }
    
    HEADER_Writer(rle->buffer, rle->size, f);

    if(test) 
    {
        displayBuffer = (uint8_t*)malloc(sizeof(uint8_t)*width*height);
        memset(displayBuffer, ' ', width*height);
        DRAW* d = (DRAW*)malloc(sizeof(DRAW));
        DRAW_Init(d, &draw);
        DRAW_CompressedBitmap(d, rle->buffer, rle->size, imageWidth, imageHeight);
        outputDisplayBuffer();
        free(displayBuffer);
    }

    RLE_Deinit(rle); // Kill RLE
    return 0;
}