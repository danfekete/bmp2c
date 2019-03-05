#include <stdio.h>
#include "bmp.h"

void main(int argc, char **argv) 
{
    printf("BMP2C 0.0.1\n");
    BMP_ReadBitmap(argv[1]);
}