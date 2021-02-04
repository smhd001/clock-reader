#include <stdio.h>
#include "myheder.h"

unsigned char learnede[2000][2000][3];
unsigned char detecte[2000][2000][3];
//int abs(int);
int c = 1;
int main()
{
    unsigned long long int dif = 0, mindif = 5021307000;
    char p[100];
    
    int a, b, c, i, j, o, k, detcted_num, saat = 0;
    int w, h;

    //scanf("%s", p);
   // crop(p);
    printf("first done");

    for (i = 1; i <= 8; i++)
    {
        if (i != 6 && i != 3)
        {
            sprintf(p, "out%d.bmp", i);
            printf("    %s\n", p);
            resize(p, 740, 887);
        }
    }
    
    //out1.bmp  ta 8 bejoz 3  va 6
    for (i = 1; i <= 8; i++)
    {
        if (i != 3 && i != 6)
        {

            sprintf(p, "out%d.bmp", i);
            readBMP(p, &w, &h, detecte);
            for (j = 0; j <= 9; j++)
            {
                sprintf(p, "fixedlearned%d.bmp", j);
                readBMP(p, &w, &h, learnede);
                for (o = 0; o < 887; o++)
                {
                    for (k = 0; k < 740; k++)
                    {
                        dif += abs(learnede[o][k][0] - detecte[o][k][0]);
                        dif += abs(learnede[o][k][1] - detecte[o][k][1]);
                        dif += abs(learnede[o][k][2] - detecte[o][k][2]);
                    }
                }
                //printf("%s\n",p);
                //printf("%d  %lld \n",j,dif);
                if (dif < mindif)
                {
                    mindif = dif;
                    detcted_num = j;
                      //  printf(" %d ",j);
                        //printf("%lld",dif);
                }
                dif = 0;
            }
            mindif = 502130700;
            printf("%d", detcted_num);
        }
    }

}
