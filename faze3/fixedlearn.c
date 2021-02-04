#include <stdio.h>
#include <bmpio.h>
#include "myheder.h"

unsigned char fix[2000][2000][3];

unsigned char siahi(int i, int j)
{
    //printf("%d", (fix[i][j][0]+fix[i][j][1]+fix[i][j][2])/3);
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
int main()
{
    unsigned long int sum = 0, n = 0,av;
    int width, hidth;
    int i, j, k;
    char p[100];
    for (k = 0; k <= 9; k++)
    {
        sprintf(p,"learned%d.bmp", k);
        readBMP(p, &width, &hidth, fix);

        for (i = 0; i < 887; i++)
        {
            for (j = 0; j < 887; j++)
            {
                if (siahi(i, j) < 150)
                {
                    sum += siahi(i, j);
                    n++;
                }
            }
        }
        av = sum / n;
        for (i = 0; i < 887; i++)
        {
            for (j = 0; j < 887; j++)
            {
                if (siahi(i, j) < 1.7*av+10)
                {
                    sia(i, j);
                }
                else
                {
                    sefid(i, j);
                }
            }
        }
        sprintf(p, "fixedlearnde%d.bmp", k);
        saveBMP(fix, 887, 887, p);
    }
}
