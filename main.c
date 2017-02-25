#include "main.h"

int main(int argc, char *argv[])
{
    PPMPIXEL *pixel1Pointer = NULL;
    PPMPIXEL *pixel2Pointer = NULL;
    PPMPIXEL *pixeloutPointer = NULL;

    FILE *input1FilePointer = NULL;
    FILE *input2FilePointer = NULL;
    FILE *outputFilePointer = NULL;

    unsigned int ppmWidth = 0;
    unsigned int ppmHeight = 0;
    unsigned int ppmBright = 0;
    unsigned int ppmWidthCompare = 0;
    unsigned int ppmHeightCompare = 0;
    unsigned int ppmBrightCompare = 0;

    unsigned int thresholdShowRed = NOCOLORPRESETTING;
    unsigned int thresholdShowGreen = NOCOLORPRESETTING;
    unsigned int thresholdShowBlue = NOCOLORPRESETTING;

    unsigned int threshold = 0;

    unsigned int rvInPixel = 0;
    unsigned int rvOutPixel = 0;
    unsigned int rvWidthHeightBright = 0;
    unsigned int rvGetOpt = 0;
    unsigned int rvclose = 0;

    unsigned int ppmIn1Type = 0;
    unsigned int ppmIn2Type = 0;
    unsigned int ppmOutType = 0;
    unsigned int inputFileCount = 0;
    unsigned int outputType1 = 0;
    unsigned int outputType2 = 0;
    unsigned int outputType3 = 0;
    unsigned int outputType4 = 0;
    unsigned int outputType5 = 0;
    unsigned int outputType6 = 0;
    unsigned int optCount = 0;
    unsigned int colCount = 0;
    unsigned int typCount = 0;
    unsigned int outCount = 0;

    char inputFile1[MAXCHARPERLINE], inputFile2[MAXCHARPERLINE];
    char outputFile1[MAXCHARPERLINE], outputFile2[MAXCHARPERLINE], outputFile3[MAXCHARPERLINE], outputFile4[MAXCHARPERLINE];
    char outputFile5[MAXCHARPERLINE], outputFile6[MAXCHARPERLINE];
    char redstring[MAXCHARPERLINE], greenstring[MAXCHARPERLINE], bluestring[MAXCHARPERLINE];
    char thresstring[MAXCHARPERLINE], typestring[MAXCHARPERLINE];

    /* main program */

    welcome();

    /* getopt handling */

    while((rvGetOpt = getopt(argc, argv, "f:s:o:v:w:x:y:z:t:r:g:b:p:h")) != -1)
    {
        switch(rvGetOpt)
        {
        case 'h':
        {
            help();
            exit(EXIT_SUCCESS);
        }
        case 'f':
        {
            catchClearOptGetString(optarg, inputFile1, "first input file");
            if(checkFileExtension(inputFile1, ".ppm") != 0)
            {
                exit(EXIT_FAILURE);
            }
            else
            {
                inputFileCount++;
            }
            break;
        }
        case 's':
        {
            catchClearOptGetString(optarg, inputFile2, "second input file");
            if(checkFileExtension(inputFile2, ".ppm") != 0)
            {
                exit(EXIT_FAILURE);
            }
            else
            {
                inputFileCount++;
            }
            break;
        }
        case 'o':
        {
            catchClearOptGetString(optarg, outputFile1, "output file");
            if(checkFileExtension(outputFile1, ".ppm") != 0)
            {
                exit(EXIT_FAILURE);
            }
            else
            {
                outputType1 = 1;
                infoTextOutput(1);
            }
            break;
        }
        case 'v':
        {
            catchClearOptGetString(optarg, outputFile2, "output file");
            if(checkFileExtension(outputFile2, ".ppm") != 0)
            {
                exit(EXIT_FAILURE);
            }
            else
            {
                outputType2 = 1;
                infoTextOutput(2);
            }
            break;
        }
        case 'w':
        {
            catchClearOptGetString(optarg, outputFile3, "output file");
            if(checkFileExtension(outputFile3, ".ppm") != 0)
            {
                exit(EXIT_FAILURE);
            }
            else
            {
                outputType3 = 1;
                infoTextOutput(3);
            }
            break;
        }
        case 'x':
        {
            catchClearOptGetString(optarg, outputFile4, "output file");
            if(checkFileExtension(outputFile4, ".ppm") != 0)
            {
                exit(EXIT_FAILURE);
            }
            else
            {
                outputType4 = 1;
                infoTextOutput(4);
            }
            break;
        }
        case 'y':
        {
            catchClearOptGetString(optarg, outputFile5, "output file");
            if(checkFileExtension(outputFile5, ".ppm") != 0)
            {
                exit(EXIT_FAILURE);
            }
            else
            {
                outputType5 = 1;
                infoTextOutput(5);
            }
            break;
        }
        case 'z':
        {
            catchClearOptGetString(optarg, outputFile6, "output file");
            if(checkFileExtension(outputFile6, ".ppm") != 0)
            {
                exit(EXIT_FAILURE);
            }
            else
            {
                outputType6 = 1;
                infoTextOutput(6);
            }
            break;
        }
        case 't':
        {
            catchClearOptGetString(optarg, thresstring, "threshold");
            if(getInteger(thresstring, &threshold, 0, 255) != 0)
            {
                exit(EXIT_FAILURE);
            }
            else
            {
                optCount++;
            }
            break;
        }
        case 'r':
        {
            catchClearOptGetString(optarg, redstring, "marker color R");
            if(getInteger(redstring, &thresholdShowRed, 0, 255) != 0)
            {
                exit(EXIT_FAILURE);
            }
            else
            {
                colCount++;
            }
            break;
        }
        case 'g':
        {
            catchClearOptGetString(optarg, greenstring, "marker color G");
            if(getInteger(greenstring, &thresholdShowGreen, 0, 255) != 0)
            {
                exit(EXIT_FAILURE);
            }
            else
            {
                colCount++;
            }
            break;
        }
        case 'b':
        {
            catchClearOptGetString(optarg, bluestring, "marker color B");
            if(getInteger(bluestring, &thresholdShowBlue, 0, 255) != 0)
            {
                exit(EXIT_FAILURE);
            }
            else
            {
                colCount++;
            }
            break;
        }
        case 'p':
        {
            catchClearOptGetString(optarg, typestring, "ppm output type");
            catchClearString(typestring);
            if(strncmp(typestring, "p3", 2) == 0)
            {
                printf("output file(s) ASCII ppm\n");
                typCount++;
                ppmOutType = 3;
            }
            else if(strncmp(typestring, "p6", 2) == 0)
            {
                printf("output file(s) BINARY ppm\n");
                typCount++;
                ppmOutType = 6;
            }
            else
            {
                fprintf(stderr, "wrong magic code for output\n");
                help();
                exit(EXIT_FAILURE);
            }
            break;
        }
        }
    }

    /* secondary getopt handling */

    if(inputFileCount != 2)
    {
        fprintf(stderr, "too less input files specified\n");
        help();
        exit(EXIT_FAILURE);
    }

    outCount = outputType1 + outputType2 + outputType3 + outputType4 + outputType5 + outputType6;
    if(outCount < 1)
    {
        fprintf(stderr, "not even one output file specified\n");
        help();
        exit(EXIT_FAILURE);
    }

    if(colCount < 3)
    {
        printf("missing color values set to %u\n", NOCOLORPRESETTING);
    }

    if(optCount == 0)
    {
        printf("no threshold specified, missing value set later to half of brightness\n");
    }

    if(typCount == 0)
    {
        fprintf(stderr, "no output format specified\n");
        help();
        exit(EXIT_FAILURE);
    }

    /* open input files and exit if something went wrong, output files checked later */

    input1FilePointer = fopen(inputFile1, "rb");
    if(input1FilePointer == NULL)
    {
        perror("ERROR opening first input file");
        exit(EXIT_FAILURE);
    }

    input2FilePointer = fopen(inputFile2, "rb");
    if(input2FilePointer == NULL)
    {
        perror("ERROR opening second input file");
        EXIT1
        exit(EXIT_FAILURE);
    }
    divline();

    if(input1FilePointer != NULL && input2FilePointer != NULL)
    {
        printf("successfully opened both input files\n");
    }
    divline();

    /* width, height and brightness for output are defined from first input file */
    /* read information input picture 1 */

    printf("header of 1st input file: %s\n", inputFile1);
    rvWidthHeightBright = getWidthHeightBright(input1FilePointer, &ppmWidth, &ppmHeight, &ppmBright, &ppmIn1Type);
    if(rvWidthHeightBright != 0)
    {
        EXIT1
        EXIT2
        exit(EXIT_FAILURE);
    }

    /* read information input picture 2 */

    printf("\nheader of 2nd input file: %s\n", inputFile2);
    rvWidthHeightBright = getWidthHeightBright(input2FilePointer, &ppmWidthCompare, &ppmHeightCompare, &ppmBrightCompare, &ppmIn2Type);
    if(rvWidthHeightBright != 0)
    {
        EXIT1
        EXIT2
        exit(EXIT_FAILURE);
    }
    divline();

    /* check if second input file has same width, height and brightness and other important options */

    if(thresholdShowRed > ppmBright || thresholdShowGreen > ppmBright || thresholdShowBlue > ppmBright)
    {
        printf("WARNING: specified marker color value exceeds brightness %u\n", ppmBright);
    }

    if(threshold == 0)
    {
        threshold = ppmBright / 2;
        printf("missing threshold set to half of brightness = %u\n", threshold);
    }

    if(threshold > ppmBright)
    {
        printf("WARNING: threshold bigger than brightness %u\n", ppmBright);
    }

    if(ppmWidth != ppmWidthCompare || ppmHeight != ppmHeightCompare || ppmBright != ppmBrightCompare)
    {
        fprintf(stderr, "error incompatible width, height or brightness\n");
        help();
        EXIT1
        EXIT2
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("pictures are compatible, width %upx height %upx brightness %u\n", ppmWidth, ppmHeight, ppmBright);
    }
    divline();

    /* read first picture into memory */

    pixel1Pointer = (PPMPIXEL *)malloc(ppmWidth*ppmHeight*sizeof(PPMPIXEL));
    if (pixel1Pointer == NULL)
    {
        perror("error allocating memory\n");
        EXIT1
        EXIT2
        exit(EXIT_FAILURE);
    }
    printf("1st input file - ");
    rvInPixel = getPPM(pixel1Pointer, input1FilePointer, inputFile1, &ppmWidth, &ppmHeight, &ppmBright, ppmIn1Type);
    if (rvInPixel != 0)
    {
        EXIT1
        EXIT2
        EXIT3
        exit(EXIT_FAILURE);
    }

    EXIT1
    rvclose = 0;
    rvInPixel = 0;

    /* read second picture into memory */

    pixel2Pointer = (PPMPIXEL *)malloc(ppmWidth*ppmHeight*sizeof(PPMPIXEL));
    if (pixel2Pointer == NULL)
    {
        perror("error allocating memory\n");
        EXIT2
        EXIT3
        exit(EXIT_FAILURE);
    }
    printf("2nd input file - ");
    rvInPixel = getPPM(pixel2Pointer, input2FilePointer, inputFile2, &ppmWidth, &ppmHeight, &ppmBright, ppmIn2Type);
    if (rvInPixel != 0)
    {
        EXIT2
        EXIT3
        EXIT4
        exit(EXIT_FAILURE);
    }

    EXIT2
    rvclose = 0;
    rvInPixel = 0;
    divline();

    /* output */

    for(int i = 0; i < outCount; i++)
    {
        pixeloutPointer = (PPMPIXEL *)malloc(ppmWidth*ppmHeight*sizeof(PPMPIXEL));
        if (pixeloutPointer == NULL)
        {
            perror("error allocating memory\n");
            EXIT3
            EXIT4
            exit(EXIT_FAILURE);
        }

        if(outputType1 == 1)
        {
            outputFilePointer = fopen(outputFile1, "wb");
            if (outputFilePointer == NULL)
            {
                perror("error output file");
                EXIT3
                EXIT4
                EXIT5
                exit(EXIT_FAILURE);
            }
            calcPPMrgb(pixel1Pointer, pixel2Pointer, &pixeloutPointer, ppmWidth, ppmHeight, threshold, thresholdShowRed, thresholdShowGreen, thresholdShowBlue, 1);
            rvOutPixel = writePPM(pixeloutPointer, outputFilePointer, outputFile1, ppmWidth, ppmHeight, ppmBright, ppmOutType);
            if (rvOutPixel != 0)
            {
                EXIT3
                EXIT4
                EXIT5
                EXIT6
                exit(EXIT_FAILURE);
            }
            EXIT5
            EXIT6
            rvclose = 0;
            outputType1 = 0;
            continue;
        }

        if(outputType2 == 1)
        {
            outputFilePointer = fopen(outputFile2, "wb");
            if (outputFilePointer == NULL)
            {
                perror("error output file");
                EXIT3
                EXIT4
                EXIT5
                exit(EXIT_FAILURE);
            }
            calcPPMrgb(pixel1Pointer, pixel2Pointer, &pixeloutPointer, ppmWidth, ppmHeight, threshold, thresholdShowRed, thresholdShowGreen, thresholdShowBlue, 2);
            rvOutPixel = writePPM(pixeloutPointer, outputFilePointer, outputFile2, ppmWidth, ppmHeight, ppmBright, ppmOutType);
            if (rvOutPixel != 0)
            {
                EXIT3
                EXIT4
                EXIT5
                EXIT6
                exit(EXIT_FAILURE);
            }
            EXIT5
            EXIT6
            rvclose = 0;
            outputType2 = 0;
            continue;
        }

        if(outputType3 == 1)
        {
            outputFilePointer = fopen(outputFile3, "wb");
            if (outputFilePointer == NULL)
            {
                perror("error output file");
                EXIT3
                EXIT4
                EXIT5
                exit(EXIT_FAILURE);
            }
            calcPPMrgb(pixel1Pointer, pixel2Pointer, &pixeloutPointer, ppmWidth, ppmHeight, threshold, thresholdShowRed, thresholdShowGreen, thresholdShowBlue, 3);
            rvOutPixel = writePPM(pixeloutPointer, outputFilePointer, outputFile3, ppmWidth, ppmHeight, ppmBright, ppmOutType);
            if (rvOutPixel != 0)
            {
                EXIT3
                EXIT4
                EXIT5
                EXIT6
                exit(EXIT_FAILURE);
            }
            EXIT5
            EXIT6
            rvclose = 0;
            outputType3 = 0;
            continue;
        }

        if(outputType4 == 1)
        {
            outputFilePointer = fopen(outputFile4, "wb");
            if (outputFilePointer == NULL)
            {
                perror("error output file");
                EXIT3
                EXIT4
                EXIT5
                exit(EXIT_FAILURE);
            }
            calcPPMrgb(pixel1Pointer, pixel2Pointer, &pixeloutPointer, ppmWidth, ppmHeight, threshold, thresholdShowRed, thresholdShowGreen, thresholdShowBlue, 4);
            rvOutPixel = writePPM(pixeloutPointer, outputFilePointer, outputFile4, ppmWidth, ppmHeight, ppmBright, ppmOutType);
            if (rvOutPixel != 0)
            {
                EXIT3
                EXIT4
                EXIT5
                EXIT6
                exit(EXIT_FAILURE);
            }
            EXIT5
            EXIT6
            rvclose = 0;
            outputType4 = 0;
            continue;
        }

        if(outputType5 == 1)
        {
            outputFilePointer = fopen(outputFile5, "wb");
            if (outputFilePointer == NULL)
            {
                perror("error output file");
                EXIT3
                EXIT4
                EXIT5
                exit(EXIT_FAILURE);
            }
            calcPPMgrey(pixel1Pointer, pixel2Pointer, &pixeloutPointer, ppmWidth, ppmHeight, threshold, thresholdShowRed, thresholdShowGreen, thresholdShowBlue, 0.299, 0.587, 0.114);
            rvOutPixel = writePPM(pixeloutPointer, outputFilePointer, outputFile5, ppmWidth, ppmHeight, ppmBright, ppmOutType);
            if (rvOutPixel != 0)
            {
                EXIT3
                EXIT4
                EXIT5
                exit(EXIT_FAILURE);
            }
            EXIT5
            EXIT6
            rvclose = 0;
            outputType5 = 0;
            continue;
        }

        if(outputType6 == 1)
        {
            outputFilePointer = fopen(outputFile6, "wb");
            if (outputFilePointer == NULL)
            {
                perror("error output file");
                EXIT3
                EXIT4
                EXIT5
                exit(EXIT_FAILURE);
            }
            calcPPMgrey(pixel1Pointer, pixel2Pointer, &pixeloutPointer, ppmWidth, ppmHeight, threshold, thresholdShowRed, thresholdShowGreen, thresholdShowBlue, 0.333, 0.333, 0.333);
            rvOutPixel = writePPM(pixeloutPointer, outputFilePointer, outputFile6, ppmWidth, ppmHeight, ppmBright, ppmOutType);
            if (rvOutPixel != 0)
            {
                EXIT3
                EXIT4
                EXIT5
                EXIT6
                exit(EXIT_FAILURE);
            }
            EXIT5
            EXIT6
            rvclose = 0;
            outputType6 = 0;
            continue;
        }
    }

    EXIT3
    EXIT4

    goodbye();

    return 0;
}
