#include "bmp.h"


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

    uint32_t bitmapSize = (file->size - file->offset) / sizeof(COLORDATA);
    COLORBUFFER *buffer = (COLORBUFFER*)malloc(sizeof(COLORBUFFER));
    BUFFER_Init(buffer, bitmapSize);
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