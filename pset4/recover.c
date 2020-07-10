#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define MAXSIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    int pic = 0;
    FILE * outfile = NULL;
    BYTE buf[MAXSIZE];
    char filename[20];
    size_t readSize;

    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE * infile = fopen(argv[1], "r");

    if (infile == NULL)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    do
    {
        readSize = fread(buf, sizeof(BYTE), MAXSIZE, infile);
        bool header = (buf[0] == 0xff) && (buf[1] == 0xd8) && (buf[2] == 0xff) && ((buf[3] & 0xf0) == 0xe0);
        if (header)
        {
            if (outfile != NULL)
                fclose(outfile);
            sprintf(filename, "%03i.jpg", pic);
            outfile = fopen(filename, "w");
            pic++;
        }
        if (outfile != NULL)
        {
            fwrite(buf, sizeof(BYTE), readSize, outfile);
        }
    } while (readSize != 0 && !feof(infile));
    fclose(outfile);
    fclose(infile);
    return 0;
}
