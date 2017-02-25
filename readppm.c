/*

changes to the version handed in for PPM invert and PPM reduce according comments:

   - added preprocessor macro with double expansion "trick" to limit fscanf %s and prevent buffer overflow
     the macro uses the MAXCHARPERLINE value which is used global in main.h for limitation of input length to generate %100s
   - format specifier changed to %zu for sizeof() in printf - %lu results in error clang linux
   - added strncmp
   - minor printf format update for screen output

Thanks to Mr. Fibich for the comments and interesting solutions!

*/

#include "main.h"

void catchClearString(char *input)
{
    for(int j = 0; j < strlen(input); j++)
    {
        input[j] = tolower(input[j]);

        if(input[j] == '\r')
        {
            input[j] = '\0';
        }
        if(input[j] == '\n')
        {
            input[j] = '\0';
        }
        if(input[j] == '\t')
        {
            input[j] = '\0';
        }
    }
    return;
}

unsigned int catchCorrectP3(char *input)
{
    for(int j = 0; j < strlen(input); j++)
    {
        if(input[j] < 48 || input[j] > 57)
        {
            fprintf(stderr, "value for RGB pixel out of range\n");
            return 1;
        }
    }
    return 0;
}

unsigned int getWidthHeightBright(FILE *input, unsigned int *width, unsigned int *height, unsigned int *bright, unsigned int *typePPM)
{
    char *pointToEnd = NULL;
    char *rvfgets = NULL;
    char line[MAXCHARPERLINE];
    unsigned int tempHeight = 0;
    unsigned int tempWidth = 0;
    unsigned int tempBright = 0;
    unsigned int rvfscanf = 0;

    rewind(input);

    rvfscanf = fscanf(input, "%" STR(MAXCHARPERLINE) "s", line);
    if(rvfscanf == EOF || rvfscanf == 0 || strlen(line) > 2)
    {
        fprintf(stderr, "error reading header\n");
        return 1;
    }
    catchClearString(line);
    rvfscanf = 0;

    printf("magic code %s ", line);
    if(strncmp(line, "p3", 2) == 0) // changed for strncmp
    {
        printf("Portable Pixmap ASCII supported\n");
        *typePPM = 3;
    }
    else if(strncmp(line, "p6", 2) == 0) // changed for strncmp
    {
        printf("Portable Pixmap Binary supported\n");
        *typePPM = 6;
    }
    else
    {
        printf("input format not supported\n");
        help();
        return 1;
    }

    rvfscanf = fscanf(input, "%" STR(MAXCHARPERLINE) "s", line);
    if(rvfscanf == EOF || rvfscanf == 0)
    {
        fprintf(stderr, "error reading header\n");
        return 1;
    }
    catchClearString(line);
    rvfscanf = 0;

    while(1)
    {
        if(line[0] == '#')
        {
            rvfgets = fgets(line, MAXCHARPERLINE, input);
            if(rvfgets == NULL)
            {
                perror("error reading header\n");
                return 1;
            }
            printf("# %s", line);
            rvfgets = NULL;
        }
        else
        {
            break;
        }

        rvfscanf = fscanf(input, "%" STR(MAXCHARPERLINE) "s", line);
        if(rvfscanf == EOF || rvfscanf == 0)
        {
            fprintf(stderr, "error reading header");
            return 1;
        }
        catchClearString(line);
        rvfscanf = 0;
    }

    tempWidth = strtoul(line, &pointToEnd, 0);
    pointToEnd = NULL;
    if(tempWidth < 1)
    {
        printf("0 or negative width or not correct char for dividing\n");
        help();
        pointToEnd = NULL;
        return 1;
    }

    rvfscanf = fscanf(input, "%" STR(MAXCHARPERLINE) "s", line);
    if(rvfscanf == EOF || rvfscanf == 0)
    {
        fprintf(stderr, "error reading header\n");
        return 1;
    }
    catchClearString(line);
    rvfscanf = 0;

    while(1)
    {
        if(line[0] == '#')
        {
            rvfgets = fgets(line, MAXCHARPERLINE, input);
            if(rvfgets == NULL)
            {
                perror("error reading header\n");
                return 1;
            }
            printf("# %s", line);
            rvfgets = NULL;
        }
        else
        {
            break;
        }

        rvfscanf = fscanf(input, "%" STR(MAXCHARPERLINE) "s", line);
        if(rvfscanf == EOF || rvfscanf == 0)
        {
            fprintf(stderr, "error reading header");
            return 1;
        }
        catchClearString(line);
        rvfscanf = 0;
    }

    tempHeight = strtoul(line, &pointToEnd, 0);
    pointToEnd = NULL;
    if(tempHeight < 1)
    {
        printf("0 or negative height or not correct char for dividing\n");
        help();
        pointToEnd = NULL;
        return 1;
    }

    printf("width %u x height %u ", tempWidth, tempHeight);

    rvfscanf = fscanf(input, "%" STR(MAXCHARPERLINE) "s", line);
    if(rvfscanf == EOF || rvfscanf == 0)
    {
        fprintf(stderr, "error reading header\n");
        return 1;
    }
    catchClearString(line);
    rvfscanf = 0;

    while(1)
    {
        if(line[0] == '#')
        {
            rvfgets = fgets(line, MAXCHARPERLINE, input);
            if(rvfgets == NULL)
            {
                perror("error reading header\n");
                return 1;
            }
            printf("# %s", line);
            rvfgets = NULL;
        }
        else
        {
            break;
        }

        rvfscanf = fscanf(input, "%" STR(MAXCHARPERLINE) "s", line);
        if(rvfscanf == EOF || rvfscanf == 0)
        {
            fprintf(stderr, "error reading header");
            return 1;
        }
        catchClearString(line);
        rvfscanf = 0;
    }

    tempBright = strtoul(line, &pointToEnd, 0);
    pointToEnd = NULL;
    if(tempBright > 255)
    {
        printf("error reading header - negative or to big brightness\n");
        printf("maybe it is a 16bit PPM - see help\n");
        help();
        return 1;
    }
    printf("brightness %u ", tempBright);
    printf("%u PIXEL total %zu MB\n", tempWidth*tempHeight, sizeof(PPMPIXEL)*tempWidth*tempHeight/1024/1024);  // format specifier changed to lu

    *width = tempWidth;
    *height = tempHeight;
    *bright = tempBright;

    return 0;
}

unsigned int getPPM(PPMPIXEL *pixel, FILE *input, char file[], unsigned int *width, unsigned int *height, unsigned int *bright, unsigned int typePPM)
{
    char red[3];
    char green[3];
    char blue[3];
    int tempValue = 0;
    int dataloop = 0;
    char *pointToEnd = NULL;
    int rvfscanf = 0;
    int rvcatch = 0;
    unsigned int temp = 0;

    printf("loading data to memory - ");

    if(typePPM == 3)
    {
        do
        {
            rvfscanf = fscanf(input, "%" STR(MAXCHARPERLINE) "s", red);
            if(rvfscanf == EOF)
            {
                fprintf(stderr, "error reading data - ");
                return 1;
            }
            catchClearString(red);
            rvcatch = catchCorrectP3(red);
            if(rvcatch != 0)
            {
                fprintf(stderr, "no valid number red - ");
                return 1;
            }
            rvcatch = 0;
            tempValue = strtoul(red, &pointToEnd, 0);
            if(tempValue < 0 || tempValue > (*bright))
            {
                fprintf(stderr, "red value - or > brightness - ");
                return 1;
            }
            (pixel+dataloop)->r = tempValue;
            tempValue = 0;
            pointToEnd = NULL;

            rvfscanf = fscanf(input, "%" STR(MAXCHARPERLINE) "s", green);
            if(rvfscanf == EOF)
            {
                fprintf(stderr, "error reading data - ");
                return 1;
            }
            catchClearString(green);
            rvcatch = catchCorrectP3(green);
            if(rvcatch != 0)
            {
                fprintf(stderr, "no valid number green - ");
                return 1;
            }
            rvcatch = 0;
            tempValue = strtoul(green, &pointToEnd, 0);
            if(tempValue < 0 || tempValue > (*bright))
            {
                fprintf(stderr, "green value - or > brightness - ");
                return 1;
            }
            (pixel+dataloop)->g = tempValue;
            tempValue = 0;
            pointToEnd = NULL;

            rvfscanf = fscanf(input, "%" STR(MAXCHARPERLINE) "s", blue);
            if(rvfscanf == EOF)
            {
                fprintf(stderr, "error reading data - ");
                return 1;
            }
            catchClearString(blue);
            rvcatch = catchCorrectP3(blue);
            if(rvcatch != 0)
            {
                fprintf(stderr, "no valid number blue - ");
                return 1;
            }
            rvcatch = 0;
            tempValue = strtoul(blue, &pointToEnd, 0);
            if(tempValue < 0 || tempValue > (*bright))
            {
                fprintf(stderr, "blue value - or > brightness - ");
                return 1;
            }
            (pixel+dataloop)->b = tempValue;
            tempValue = 0;
            pointToEnd = NULL;

            dataloop++;
        }
        while(dataloop < (*height)*(*width));
    }

    if(typePPM == 6)
    {
        temp = fgetc(input);
        if(temp == EOF)
        {
            fprintf(stderr, "error reading binary pixel - ");
            return 1;
        }

        while(dataloop < (*height)*(*width))
        {
            (pixel+dataloop)->r = fgetc(input);
            if((pixel+dataloop)->r == EOF)
            {
                fprintf(stderr, "error reading binary pixel - ");
                return 1;
            }
            (pixel+dataloop)->g = fgetc(input);
            if((pixel+dataloop)->g == EOF)
            {
                fprintf(stderr, "error reading binary pixel - ");
                return 1;
            }
            (pixel+dataloop)->b = fgetc(input);
            if((pixel+dataloop)->b == EOF)
            {
                fprintf(stderr, "error reading binary pixel - ");
                return 1;
            }
            dataloop++;
        }
    }

    printf("%s - %d PIXEL read\n", file, dataloop);
    return 0;
}
