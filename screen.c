#include "main.h"

void help()
{
    divline();
    printf("help section, find here some useful infos\n");
    divline();
    printf("example call with all arguments, arbitrary order of arguments possible\n");
    divline();
    printf("\nsubtract.exe -f inp1.ppm -s inp2.ppm -o out1.ppm -v out2.ppm -w out3.ppm\n");
    printf("             -x out4.ppm -y out5.ppm -z out6.ppm -t 40 -p p6 -r 255 -g 255 -b 255\n\n");
    divline();
    printf("description of the arguments, OPT optional, REQ required\n");
    divline();
    printf("\nINPUT arguments\n\n");
    printf("-f inp1.ppm\tREQ\t1st input image\n");
    printf("this is be the neutral / reference picture\n\n");
    printf("-s inp2.ppm\tREQ\t2nd input image (move)\n");
    printf("this is be the picture with the moving element(s)\n\n");
    printf("## P3 and P6 ppm possible, the first input file -f is the reference for width,\n");
    printf("   height and brightness, the second file is checked if compatible\n\n");
    printf("OUTPUT arguments\n\n");
    printf("-o out1.ppm\tOPT\toutput type 1\n");
    infoTextOutput(1);
    printf("\n-v out2.ppm\tOPT\toutput type 2\n");
    infoTextOutput(2);
    printf("\n-w out3.ppm\tOPT\toutput type 3\n");
    infoTextOutput(3);
    printf("\n-x out4.ppm\tOPT\toutput type 4\n");
    infoTextOutput(4);
    printf("\n-y out5.ppm\tOPT\toutput type 5\n");
    infoTextOutput(5);
    printf("\n-z out6.ppm\tOPT\toutput type 6\n");
    infoTextOutput(6);
    printf("\n## one output type must be specified (REQ), arbitrary combinations possible\n\n");
    printf("## R&G&B:           all color values of one pixel must exceed given threshold value\n");
    printf("                    and the red, green, blue value of every pixel is checked\n");
    printf("   weighted GREY:   the weighted grey value must exceed given threshold, every pixel is converted\n");
    printf("                    0.299 red * 0.587 green * 0.114 blue for the calculation\n");
    printf("   unweighted GREY: the unweighted grey value must exceed given threshold, every pixel is converted\n");
    printf("                    0.333 red * 0.333 green * 0.333 blue for the calculation\n\n");
    printf("OPTIONS for calculation and output\n\n");
    printf("-t 40\tOPT\tthreshhold value\n\n");
    printf("## this is the main value for the calculation(s), moving object is detected when\n");
    printf("   abs [ (color value pixel input 2) - (color value pixel input 1) ] > threshold\n");
    printf("   value check with brightness of input images during processing input files\n");
    printf("   if no value is given missing threshold is set to half of brightness\n\n");
    printf("-p p6\tREQ\toutput format for picture\n\n");
    printf("## p3 for ASCII and p6 for BIN ppm file\n\n");
    printf("-r 255\tOPT\tred value for the marker\n");
    printf("-g 255\tOPT\tgreen value for the marker\n");
    printf("-b 255\tOPT\tblue value for the marker\n\n");
    printf("## presetting 255, missing value will be set to this value\n");
    printf("   numbers are checked for validity, no chars to be included\n\n");
    divline();
    printf("further remarks PPM file handling\n");
    divline();
    printf("- comments in ASCII P3 or BINARY P6 input files are cut at 80 chars\n");
    printf("- output file(s) do not include the comments from input file(s)\n");
    printf("- comments in PPM file are allowed in all header but not after brightness\n");
    printf("- if input file/s has/have float numbers color value(s) -> typecast to integer\n");
    printf("- if input file/s has/have to much pixel the rest after width*height is ignored\n");
    printf("- tool supports only 8 bit PPM with brightness 0-255\n");
    printf("- input files are checked for correct values before handling the calculations\n");
    divline();
    printf("\n");
}

void welcome()
{
    divline();
    printf("welcome to the PPM Image Subtraction tool by el16b005 Helmut Resch\n");
    divline();
}

void divline()
{
    printf("---------------------------------------------------------------------------------------------------\n");
}

unsigned int checkFileExtension(char *input, char *ext)
{
    for (int k = strlen(input); k < strlen(input) - 3; k--)
    {
        input[k] = tolower(input[k]);
    }

    if(strncmp(&(input[(strlen(input)-4)]),ext, 4) != 0)
    {
        printf("not correct file extension or file > %d chars\n", MAXCHARPERLINE);
        help();
        return 1;
    }
    else
    {
        printf("syntax OK\n");
        return 0;
    }
}

void goodbye()
{
    printf("\nyou can check the output files in your program directory\n");
}

unsigned int getInteger(char *input, unsigned int *numInteger, unsigned int lo, unsigned int hi)
{
    unsigned int number = 0;
    char *pointToEnd = NULL;

    number = strtoul(input, &pointToEnd, 0);

    if(pointToEnd == input || *pointToEnd != '\0')
    {
        printf("integer conversion error\n");
        help();
        return 1;
    }
    else
    {
        if(number < lo || number > hi)
        {
            fprintf(stderr, " > %u or < %u\n", hi, lo);
            help();
            return 1;
        }
        else
        {
            printf("range OK\n");
            *numInteger = number;
            return 0;
        }
    }
}

void catchClearOptGetString(char *in, char *out, char *text)
{
    strncpy(out, in, strlen(in));
    out[strlen(in)] = '\0';
    printf("%s - %s - ", out, text);
}

void infoTextOutput(unsigned int typ)
{
    switch(typ)
    {
    case(1):
    {
        printf("description: below threshold neutral color, above threshold highlight color, R&G&B\n");
        break;
    }
    case(2):
    {
        printf("description: below threshold color first input, above threshold highlight color, R&G&B\n");
        break;
    }
    case(3):
    {
        printf("description: below threshold color first input, above threshold highlight color, transparency, R&G&B\n");
        break;
    }
    case(4):
    {
        printf("description: below threshold neutral color, above threshold color second input, R&G&B\n");
        break;
    }
    case(5):
    {
        printf("description: below threshold neutral color, above threshold highlight color, weighted GREY\n");
        break;
    }
    case(6):
    {
        printf("description: below threshold neutral color, above threshold highlight color, unweighted GREY\n");
        break;
    }
    default:
    {
        break;
    }
    }
}
