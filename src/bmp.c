#include "bmp.h"

int BMP_ReadBitmap(const char *fname)
{
    FILE *f = fopen(fname, "rb");
    if(f == NULL) return NULL;

    uint16_t magic, offset;
    fread(&magic, sizeof(uint16_t), 1, f);
    if (magic != 0x4D42)
    {
        printf("Not bitmap!\n");
        fclose(f);
        return NULL;
    }

    fseek(f, 0x0A, SEEK_SET);
    fread(&offset, sizeof(uint16_t), 1, f);
    fseek(f, offset, SEEK_SET);


    /*BITMAPFILEHEADER header;
    BITMAPINFOHEADER info;

    fread(&header, sizeof(BITMAPFILEHEADER), 1, f);
    printf("Type: %X\n", header.bfType);
    printf("Off bits: %X\n", header.bfOffBits);

    if (header.bfType != 0x4D42)
    {
        printf("Not bitmap!\n");
        fclose(f);
        return NULL;
    }*/

    //fread(&info, sizeof(BITMAPINFOHEADER), 1, f);
    //fseek(f, header.bfOffBits, SEEK_SET);
    
    int c = NULL;
    while (c != EOF)
    {
        char comma = ',';
        c = fgetc(f);
        if(c != NULL) {
            printf("%c0x%02x ", comma, c);
        }
    } 

    fclose(f);

    return 1;
}