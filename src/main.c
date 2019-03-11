#include <stdio.h>
#include "bmp.h"
#include "mono.h"
#include "rle.h"
#include "h_writer.h"
#include "../argparse/argparse.h"

static const char *const usage[] = {
    "bmp2c [options] filename",
    NULL,
};

int main(int argc, char **argv) 
{
    float dither = 0.5;
    const char *path = NULL;
    const unsigned char floyd;

    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_STRING('o', "output", &path, "Output"),
        OPT_FLOAT('d', "dither", &dither, "Dither threshold"),
        OPT_BOOLEAN('f', 'floyd', &floyd, "Use Floyd-Steinberg algorithm to dither"),
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

    RLE_Deinit(rle); // Kill RLE
    return 0;
}