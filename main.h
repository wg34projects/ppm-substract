#ifndef MAIN_H__
#define MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include <math.h>

#define MAXCHARPERLINE 100

#define STR1(x)  #x
#define STR(x)  STR1(x)

#define BLACKPRESETTING 0
#define NOCOLORPRESETTING 255
#define TRANSPARENCY 50

#define EXIT1       rvclose = fclose(input1FilePointer);\
                    if(rvclose != 0)\
                    {\
                        fprintf(stderr, "error closing input file\n");\
                    }\
                    input1FilePointer = NULL;

#define EXIT2       rvclose = fclose(input2FilePointer);\
                    if(rvclose != 0)\
                    {\
                        fprintf(stderr, "error closing input file\n");\
                    }\
                    input2FilePointer = NULL;

#define EXIT3       free(pixel1Pointer);\
                    pixel1Pointer = NULL;

#define EXIT4       free(pixel2Pointer);\
                    pixel2Pointer = NULL;

#define EXIT5       free(pixeloutPointer);\
                    pixeloutPointer = NULL;

#define EXIT6       fclose(outputFilePointer);\
                    outputFilePointer = NULL;

struct ppmPixel
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
};

typedef struct ppmPixel PPMPIXEL;

void help();
void divline();
void welcome();
void infoTextOutput(unsigned int typ);
void goodbye();
void catchClearOptGetString(char *in, char *out, char *text);
void catchClearString(char *input);
unsigned int getInteger(char *input, unsigned int *numInteger, unsigned int lo, unsigned int hi);
unsigned int checkFileExtension(char *input, char *ext);
unsigned int getWidthHeightBright(FILE *input, unsigned int *width, unsigned int *height, unsigned int *bright, unsigned int *typePPM);
unsigned int getPPM(PPMPIXEL *pixel, FILE *input, char file[], unsigned int *width, unsigned int *height, unsigned int *bright, unsigned int typePPM);
void calcPPMrgb(PPMPIXEL *pixel1, PPMPIXEL *pixel2, PPMPIXEL **pixel3, unsigned int width, unsigned int height, unsigned int thres, unsigned int red, unsigned int green, unsigned int blue, unsigned int typ);
void calcPPMgrey(PPMPIXEL *pixel1, PPMPIXEL *pixel2, PPMPIXEL **pixel3, unsigned int width, unsigned int height, unsigned int thres, unsigned int red, unsigned int green, unsigned int blue, float rWeight, float gWeight, float bWeight);
unsigned int writePPM(PPMPIXEL *pixel, FILE *output, char file[], unsigned int width, unsigned int height, unsigned int bright, unsigned int typePPM);

#endif // MAIN_H__
