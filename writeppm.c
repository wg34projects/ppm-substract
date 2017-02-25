/*

changes to the version handed in for PPM invert and PPM reduce according comments:

   - changed if(rvfprintf < 0) to 3 as minimum 3 pixelvalues MUST be written

*/

#include "main.h"

unsigned int writePPM(PPMPIXEL *pixel, FILE *output, char file[], unsigned int width, unsigned int height, unsigned int bright, unsigned int typePPM)
{
    int rvfprintf = 0;

    printf("writing to output file %s, this may take a while", file);
    if(typePPM == 3)
    {
        rvfprintf = fprintf(output, "P3\n");
        if(rvfprintf < 0)
        {
            fprintf(stderr, "error writing to output file\n");
            return 1;
        }
        else
        {
            rvfprintf = 0;
        }
    }
    else
    {
        rvfprintf = fprintf(output, "P6\n");
        if(rvfprintf < 0)
        {
            fprintf(stderr, "error writing to output file\n");
            return 1;
        }
        else
        {
            rvfprintf = 0;
        }
    }
    rvfprintf = fprintf(output, "# PRG BEL1 PPM task\n");
    if(rvfprintf < 0)
    {
        fprintf(stderr, "error writing to output file\n");
        return 1;
    }
    else
    {
        rvfprintf = 0;
    }

    rvfprintf = fprintf(output, "# created by el16b005 BEL1 helmut resch\n");
    if(rvfprintf < 0)
    {
        fprintf(stderr, "error writing to output file\n");
        return 1;
    }
    else
    {
        rvfprintf = 0;
    }

    rvfprintf = fprintf(output, "%u %u\n", width, height);
    if(rvfprintf < 0)
    {
        fprintf(stderr, "error writing to output file\n");
        return 1;
    }
    else
    {
        rvfprintf = 0;
    }

    rvfprintf = fprintf(output, "%u\n", bright);
    if(rvfprintf < 0)
    {
        fprintf(stderr, "error writing to output file\n");
        return 1;
    }
    else
    {
        rvfprintf = 0;
    }

    for(int i = 0; i < width*height; i++)
    {
        if(typePPM == 3) // ASCII OUT
        {
            rvfprintf = fprintf(output, "%u %u %u\n", (pixel+i)->r, (pixel+i)->g, (pixel+i)->b);
            if(rvfprintf < 0)
            {
                fprintf(stderr, "error writing to output file\n");
                return 1;
            }
            else
            {
                rvfprintf = 0;
            }
        }
        else // BINARY OUT
        {
            rvfprintf = fprintf(output, "%c%c%c", (pixel+i)->r, (pixel+i)->g, (pixel+i)->b);
            if(rvfprintf < 3) // prevouis < 0 but 3 pixelvalues MUST be written
            {
                fprintf(stderr, "error writing to output file\n");
                return 1;
            }
            else
            {
                rvfprintf = 0;
            }
        }
    }

    printf(" - success\n");
    return 0;
}
