#include <stdio.h>
#include <bmpio.h>
#include "myheder.h"
int c = 1;
unsigned char learn[2000][2000][3];
unsigned char temp[2000][2000][3];
void sefrer_learn();
int main()
{
    char p[100];
    int i, j, height, width, o, k;
    // scanf("%99s",p);
    
    for (i = 0; i <= 9; i++)
    {
        for (j = 1; j <= 15; j++)
        {
            sprintf(p, "./dataset/%d/%d.bmp", i, j);
            crop(p);
            c++;
        }
    }
    printf("done\n");
    c = 1;

    for (i = 0; i <= 9; i++)
    {
        for (j = 1; j <= 15; j++)
        {
            sprintf(p, "out%d.bmp", c);
            resize(p, 740, 887);
            c++;
        }
    }
    //start learning
    for (i = 0; i <= 9; i++)
    {
        sefrer_learn();
        for (j = 1; j <= 15; j++)
        {
            sprintf(p, "outre%d.bmp", i * 15 + j);
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
