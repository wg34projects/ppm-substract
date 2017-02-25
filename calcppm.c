#include "main.h"

void calcPPMrgb(PPMPIXEL *pixel1, PPMPIXEL *pixel2, PPMPIXEL **pixel3, unsigned int width, unsigned int height, unsigned int thres, unsigned int red, unsigned int green, unsigned int blue, unsigned int typ)
{
    int r = 0;
    int g = 0;
    int b = 0;

    if(typ > 4)
    {
        printf("WARNING: type 1 to 4 only - not defined output ");
        return;
    }

    printf("calculating pixel... be patient - ");
    for(int i = 0; i < width*height; i++)
    {
        r = (pixel2+i)->r - (pixel1+i)->r;
        r = abs(r);
        g = (pixel2+i)->g - (pixel1+i)->g;
        g = abs(g);
        b = (pixel2+i)->b - (pixel1+i)->b;
        b = abs(b);

        if(r <= thres && g <= thres && b <= thres)
        {
            if(typ == 1)
            {
                (*pixel3+i)->r = BLACKPRESETTING;
                (*pixel3+i)->g = BLACKPRESETTING;
                (*pixel3+i)->b = BLACKPRESETTING;
            }
            if(typ == 2)
            {
                (*pixel3+i)->r = (pixel1+i)->r;
                (*pixel3+i)->g = (pixel1+i)->g;
                (*pixel3+i)->b = (pixel1+i)->b;
            }
            if(typ == 3)
            {
                (*pixel3+i)->r = (pixel1+i)->r;
                (*pixel3+i)->g = (pixel1+i)->g;
                (*pixel3+i)->b = (pixel1+i)->b;
            }
            if(typ == 4)
            {
                (*pixel3+i)->r = BLACKPRESETTING;
                (*pixel3+i)->g = BLACKPRESETTING;
                (*pixel3+i)->b = BLACKPRESETTING;
            }
        }
        else
        {
            if(typ == 1)
            {
                (*pixel3+i)->r = red;
                (*pixel3+i)->g = green;
                (*pixel3+i)->b = blue;
            }
            if(typ == 2)
            {
                (*pixel3+i)->r = red;
                (*pixel3+i)->g = green;
                (*pixel3+i)->b = blue;
            }
            if(typ == 3)
            {
                if(red != 0 && (pixel1+i)->r != 0)
                {
                    (*pixel3+i)->r = (red + (pixel1+i)->r) / (100 / TRANSPARENCY);
                }
                else
                {
                    (*pixel3+i)->r = 0;
                }

                if(green != 0 && (pixel1+i)->g != 0)
                {
                    (*pixel3+i)->g = (green + (pixel1+i)->g) / (100 / TRANSPARENCY);
                }
                else
                {
                    (*pixel3+i)->g = 0;
                }

                if(blue != 0 && (pixel1+i)->b != 0)
                {
                    (*pixel3+i)->b = (blue + (pixel1+i)->b) / (100 / TRANSPARENCY);
                }
                else
                {
                    (*pixel3+i)->b = 0;
                }
            }
            if(typ == 4)
            {
                (*pixel3+i)->r = (pixel2+i)->r;
                (*pixel3+i)->g = (pixel2+i)->g;
                (*pixel3+i)->b = (pixel2+i)->b;
            }
        }
    }
}

void calcPPMgrey(PPMPIXEL *pixel1, PPMPIXEL *pixel2, PPMPIXEL **pixel3, unsigned int width, unsigned int height, unsigned int thres, unsigned int red, unsigned int green, unsigned int blue, float rWeight, float gWeight, float bWeight)
{
    float grey1 = 0;
    float grey2 = 0;
    int greyComp = 0;

    if(rWeight == 0 || gWeight == 0 || bWeight == 0)
    {
        printf("wrong weight values - no calculation ");
        return;
    }

    printf("calculating pixel... be patient - ");
    for(int i = 0; i < width*height; i++)
    {
        grey1 = (rWeight * (pixel1+i)->r) + (gWeight * (pixel1+i)->g) + (bWeight * (pixel1+i)->b);
        grey2 = (rWeight * (pixel2+i)->r) + (gWeight * (pixel2+i)->g) + (bWeight * (pixel2+i)->b);
        greyComp = (int)(fabs(grey2 - grey1) + 0.5);

        if(greyComp <= thres)
        {
            (*pixel3+i)->r = BLACKPRESETTING;
            (*pixel3+i)->g = BLACKPRESETTING;
            (*pixel3+i)->b = BLACKPRESETTING;
        }
        else
        {
            (*pixel3+i)->r = red;
            (*pixel3+i)->g = green;
            (*pixel3+i)->b = blue;
        }
    }
}
