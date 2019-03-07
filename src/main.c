#include <stdio.h>
#include "bmp.h"
#include "mono.h"
#include "rle.h"
#include "h_writer.h"
#include "../argparse/argparse.h"

int main(int argc, char **argv) 
{
    //printf("BMP2C 0.0.1\n");
    COLORBUFFER *buf =  BMP_ReadBitmap(argv[1]);
    MONOBUFFER *mono = (MONOBUFFER*)malloc(sizeof(MONOBUFFER));
    RLE *rle = (RLE*)malloc(sizeof(RLE));
    
    BUFFER_Grayscale(buf);
    MONO_Init(mono, buf->width, buf->height);
    MONO_FromBuffer(mono, buf);
    BUFFER_Deinit(buf); // kill the buffer
    
    MONO_FloydSteinberg(mono, 0.5);
    MONO_Threshold(mono, 0.5);
    
    RLE_Init(rle);
    RLE_FromMono(rle, mono);
    RLE_Finish(rle);
    //RLE_Write(rle, stdout);
    
    MONO_Deinit(mono); // Kill mono

    HEADER_Writer(rle->buffer, rle->size, stdout);

    RLE_Deinit(rle); // Kill RLE
    return 0;
}