#include <stdio.h>
#include "bmp.h"

int main(int argc, char **argv) 
{
    //printf("BMP2C 0.0.1\n");
    COLORBUFFER *buf =  BMP_ReadBitmap(argv[1]);
    BUFFER_Grayscale(buf);
    BUFFER_FlushPPM(buf, stdout);
    
    BUFFER_Deinit(buf);
    return 0;
}