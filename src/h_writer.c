#include "h_writer.h"

void HEADER_Writer(uint8_t *buffer, uint32_t size, FILE *out)
{
    fprintf(out, "/* generated using bmp2c */\nunsigned int data_size = %d;\nunsigned char data[] = {\n", size);

    for(int i=0; i<size; i++) 
    {
        if(i > 0) fprintf(out, ", ");
        fprintf(out, "0x%X", buffer[i]);
        if(i % 15 == 0 && i > 0) fprintf(out, "\n");
    }

    fprintf(out, "\n};");
}
