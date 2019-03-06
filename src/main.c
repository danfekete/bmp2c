#include <stdio.h>
#include "bmp.h"
#include "mono.h"

int main(int argc, char **argv) 
{
    //printf("BMP2C 0.0.1\n");
    COLORBUFFER *buf =  BMP_ReadBitmap(argv[1]);
    MONOBUFFER *mono = (MONOBUFFER*)malloc(sizeof(MONOBUFFER));
    BUFFER_Grayscale(buf);
    MONO_Init(mono, buf->width, buf->height);
    MONO_FromBuffer(mono, buf);
    BUFFER_Deinit(buf);
    MONO_FloydSteinberg(mono, 0.7f);
    MONO_FlushPPM(mono, stdout);
    MONO_Deinit(mono);
    return 0;
}