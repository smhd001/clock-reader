#include <stdio.h>
#include <bmpio.h>
#include "myheder.h"
int c = 1;
unsigned char learn[2000][2000][3];
unsigned char temp[2000][2000][3];
unsigned char fix[2000][2000][3];

unsigned char siahi(int i, int j)
{
    return (fix[i][j][0] + fix[i][j][1] + fix[i][j][2]) / 3;
}
void sia(int i, int j)
{
    fix[i][j][0] = 0;
    fix[i][j][1] = 0;
    fix[i][j][2] = 0;
}
void sefid(int i, int j)
{
    fix[i][j][0] = 255;
    fix[i][j][1] = 255;
    fix[i][j][2] = 255;
}
void sefrer_learn();
int main()
{
    char p[100];
    int i, j, height, width, o, k;
    for (i = 0; i <= 9; i++)
    {
        for (j = 1; j <= 15; j++)
        {
            sprintf(p, "./dataset/%d/%d.bmp", i, j);
            crop(p);
        }
    }

    printf("crop done done\n");

    c = 1;

    for (i = 0; i <= 9; i++)
    {
        for (j = 1; j <= 15; j++)
        {
            sprintf(p, "out%d.bmp", i * 15 + j);
            resize(p, 740, 887);
        }
    }

    printf("resize done");
    //start learning
    for (i = 0; i <= 9; i++)
    {
        sefrer_learn();
        for (j = 1; j <= 15; j++)
        {
            sprintf(p, "out%d.bmp", i * 15 + j);
            readBMP(p, &width, &height, temp);
            printf("%d   %d  ", width, height);
            printf("%s", p);

            for (o = 0; o < 887; o++)
            {
                for (k = 0; k < 740; k++)
                {

                    learn[o][k][0] += (int)(temp[o][k][0] / 15);
                    learn[o][k][1] += (int)(temp[o][k][1] / 15);
                    learn[o][k][2] += (int)(temp[o][k][2] / 15);
                }
            }
        }
        sprintf(p, "learned%d.bmp", i);
        saveBMP(learn, 740, 887, p);
    }
    printf("learning done");
    //start fix

    unsigned long int sum = 0, n = 0, av;

    for (k = 0; k <= 9; k++)
    {
        sprintf(p, "learned%d.bmp", k);
        readBMP(p, &width, &height, fix);
        if (k < 5)
        {
            for (i = 0; i < 887; i++)
            {
                for (j = 0; j < 740; j++)
                {
                    if (siahi(i, j) < 140)
                    {
                        sia(i, j);
                    }
                    else
                    {
                        sefid(i, j);
                    }
                }
            }
        }
        else
        {
            for (i = 0; i < 887; i++)
            {
                for (j = 0; j < 740; j++)
                {
                    if (siahi(i, j) < 200)
                    {
                        sia(i, j);
                    }
                    else
                    {
                        sefid(i, j);
                    }
                }
            }
        }
        sprintf(p, "fixedlearned%d.bmp", k);
        saveBMP(fix, 740, 887, p);
    }
    printf("fixing done");
}
void sefrer_learn()
{
    int o, k;
    for (o = 0; o < 887; o++)
    {
        for (k = 0; k < 740; k++)
        {

            learn[o][k][0] = 0;
            learn[o][k][1] = 0;
            learn[o][k][2] = 0;
        }
    }
}
