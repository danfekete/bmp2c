#include "bmp.h"
#include <math.h>

COLORBUFFER* BMP_ReadBitmap(const char *fname)
{
    FILE *f = fopen(fname, "rb");
    if(f == NULL) return NULL;

    uint16_t magic;
    uint32_t offset, size;
    BMP_FileStruct *file = (BMP_FileStruct*)malloc(sizeof(BMP_FileStruct));
    fseek(f, 0, SEEK_SET);
    fread(file, sizeof(BMP_FileStruct), 1, f);
    if (file->magic != 0x4D42)
    {
        printf("Not bitmap!\n");
        fclose(f);
        return NULL;
    }
    int32_t width = 0, height = 0;
    fseek(f, 0x12, SEEK_SET);
    
    fread(&width, sizeof(int32_t), 1, f);
    fread(&height, sizeof(int32_t), 1, f);
    
    uint32_t bitmapSize = abs(width) * abs(height); //(file->size - file->offset) / sizeof(COLORDATA);
    COLORBUFFER *buffer = (COLORBUFFER*)malloc(sizeof(COLORBUFFER));
    BUFFER_Init(buffer, bitmapSize, abs(width), abs(height));
    fseek(f, file->offset, SEEK_SET);
    
    COLORDATA c; // 
    while (!feof(f))
    {
        fread(&c, sizeof(COLORDATA), 1, f);
        BUFFER_AddColor(buffer, &c);
    } 

    fclose(f);
    
    free(file);
    
    return buffer;
}