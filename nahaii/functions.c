#include <stdio.h>
#include <bmpio.h>
#include "myheder.h"

unsigned char pic[2000][2000][3];
unsigned char tmp[2000][2000][3];
extern int c;

int i_tasefid       (int jmin, int jmax, int imin, int imax);
int j_tasefid  (int jmin, int jmax, int imin, int imax);
int i_tasiah        (int jmin, int jmax, int imin, int imax);
int j_tasiah   (int jmin, int jmax, int imin, int imax);
int i_tasiahp       (int jmin, int jmax, int imin, int imax);
int j_tasiahp  (int jmin, int jmax, int imin, int imax);
void cparry         (int jmin, int jmax, int imin, int imax);
int hazfehashie(int jmin, int jmax, int imin, int imax);
int sefidi          (int i, int j);

void crop(char p[100])
{
    //char p[100];
    //scanf("%99s", p);
    int imin = 0, imax = 0, jmin = 0, jmax = 0;
    int width, height;
    readBMP(p, &width, &height, pic);
    while (imax != -1 && imin != -1)
    {
        jmin = 0;
        jmax = 0;
        imin = i_tasiah(jmin + 1, width, imin + 1, height);
        imax = i_tasefid(jmin + 1, width, imin + 1, height);
        jmin = j_tasiah(jmin + 1, width, imin + 1, height);
        jmax = j_tasefid(jmin + 1, width, imin + 1, height);

        if (imax == -1 || imin == -1 || jmax == -1 || jmin == -1)
        {
            break;
        }
        while (jmin != -1 && jmax != -1)
        {
            hazfehashie(jmin, jmax, imin, imax);
            //     c++;
            jmin = jmax;
            jmin = j_tasiah(jmin + 1, width, imin + 1, height);
            jmax = j_tasefid(jmin + 1, width, imin + 1, height);
        }
        imin = imax;
        //      c++;
    }
}
void cparry(int jmin, int jmax, int imin, int imax)
{
    int i, j, k, x, y;
    for (i = imin, y = 0; i <= imax; i++, y++)
    {
        for (j = jmin, x = 0; j <= jmax; j++, x++)
        {
            for (k = 0; k < 3; k++)
            {
                tmp[y][x][k] = pic[i][j][k];
            }
        }
    }
}

int sefidi(int i, int j)
{
    if (pic[i][j][0] == 255 && pic[i][j][1] == 255 && pic[i][j][2] == 255)
    {
        return 1;
    }
    return 0;
}
int i_tasefid(int jmin, int jmax, int imin, int imax)
{
    int i, j, e = 1;
    for (i = imin; i < imax; i++)
    {
        for (j = jmin; j < jmax; j++)
        {
            if (!sefidi(i, j))
            {
                e = 0;
                break;
            }
        }
        if (e)
        {
            return i;
        }
        e = 1;
    }
    return -1;
}
int j_tasefid(int jmin, int jmax, int imin, int imax)
{
    int i, j, e;
    for (j = jmin; j < jmax; j++)
    {
        for (i = imin; i < imax; i++)
        {
            if (!sefidi(i, j))
            {
                e = 0;
                break;
            }
        }
        if (e)
        {
            return j;
        }
        e = 1;
    }
    return -1;
}
int i_tasiah(int jmin, int jmax, int imin, int imax)
{
    int i, j;
    for (i = imin; i < imax; i++)
    {
        for (j = jmin; j < jmax; j++)
        {
            if (!sefidi(i, j))
            {
                return i;
            }
        }
    }
    return -1;
}
int j_tasiah(int jmin, int jmax, int imin, int imax)
{
    int i, j;
    for (j = jmin; j < jmax; j++)
    {
        for (i = imin; i < imax; i++)
        {
            if (!sefidi(i, j))
            {
                return j;
            }
        }
    }
    return -1;
}
int i_tasiahp(int jmin, int jmax, int imin, int imax)
{
    int i, j;
    for (i = imax - 1; i > imin; i--)
    {
        for (j = jmax - 1; j > jmin; j--)
        {
            if (!sefidi(i, j))
            {
                return i;
            }
        }
    }
    return -1;
}
int j_tasiahp(int jmin, int jmax, int imin, int imax)
{
    int i, j;
    for (j = jmax - 1; j > jmin; j--)
    {
        for (i = imax - 1; i > imin; i--)
        {
            if (!sefidi(i, j))
            {
                return j;
            }
        }
    }
    return -1;
}
int hazfehashie(int jmin, int jmax, int imin, int imax)
{
    char name[50];
    //extern int c;
    cparry(j_tasiah(jmin, jmax, imin, imax), j_tasiahp(jmin, jmax, imin, imax), i_tasiah(jmin, jmax, imin, imax), i_tasiahp(jmin, jmax, imin, imax));
    int x = -j_tasiah(jmin, jmax, imin, imax) + j_tasiahp(jmin, jmax, imin, imax);
    int y = -i_tasiah(jmin, jmax, imin, imax) + i_tasiahp(jmin, jmax, imin, imax);
    sprintf(name, "out%d.bmp", c);
    printf("%s", name);
    //c++;
    saveBMP(tmp, x + 1, y + 1, name);
    if (x > 10)
    {
        c++;
    }
    return 0;
}

unsigned char out[2000][2000][3];
;

void xbozorg(double nesbat, int nwidth, int height);
void ybozorg(double nesbat, int nwidth, int nheight);

void resize(char p[100], int nwidth, int nheight)
{

    //scanf("%99s", p);
    char name[100];
    int i, j;
    int width, height;
    readBMP(p, &width, &height, pic);
    //scanf("%d%d", &, &);
    double x_nesbat = nwidth * 1.0 / width;
    double y_nesbat = nheight * 1.0 / height;
    xbozorg(x_nesbat, nwidth, height);
    ybozorg(y_nesbat, nwidth, nheight);
    //    sprintf(name,"outre%d.bmp",c);
    printf("%s", p);
    saveBMP(out, nwidth, nheight, p);
}
void xbozorg(double nesbat, int nwidth, int height)
{
    int i, k = 0, j = 0;
    double a = nesbat;
    for (i = 0; i < height; i++)
    {
        a = nesbat;

        while (j < nwidth)
        {
            while (a >= 1)
            {
                tmp[i][j][0] = pic[i][k][0];
                tmp[i][j][1] = pic[i][k][1];
                tmp[i][j][2] = pic[i][k][2];
                a--;
                j++;
            }
            if (j >= nwidth)
            {
                break;
            }
            tmp[i][j][0] = (int)(a * pic[i][k][0]);
            tmp[i][j][1] = (int)(a * pic[i][k][1]);
            tmp[i][j][2] = (int)(a * pic[i][k][2]);
            k++;
            tmp[i][j][0] += (int)((1 - a) * pic[i][k][0]);
            tmp[i][j][1] += (int)((1 - a) * pic[i][k][1]);
            tmp[i][j][2] += (int)((1 - a) * pic[i][k][2]);
            j++;
            a = nesbat - (1 - a);
        }
        k = 0;
        j = 0;
    }
}
void ybozorg(double nesbat, int nwidth, int nheight)
{
    int i = 0, k = 0, j = 0;
    double a = nesbat;
    for (j = 0; j < nwidth; j++)
    {
        a = nesbat;

        while (i < nheight)
        {
            while (a >= 1)
            {
                out[i][j][0] = tmp[k][j][0];
                out[i][j][1] = tmp[k][j][1];
                out[i][j][2] = tmp[k][j][2];
                a--;
                i++;
            }
            if (i >= nheight)
            {
                break;
            }
            out[i][j][0] = (int)(a * tmp[k][j][0]);
            out[i][j][1] = (int)(a * tmp[k][j][1]);
            out[i][j][2] = (int)(a * tmp[k][j][2]);
            k++;
            out[i][j][0] += (int)((1 - a) * tmp[k][j][0]);
            out[i][j][1] += (int)((1 - a) * tmp[k][j][1]);
            out[i][j][2] += (int)((1 - a) * tmp[k][j][2]);
            i++;
            a = nesbat - (1 - a);
        }
        k = 0;
        i = 0;
    }
}

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
int learning()
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

            printf(" %s \n", p);

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
    return 1;
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

unsigned char learned[2000][2000][3];
unsigned char detect[2000][2000][3];

int detecting()
{
    unsigned long long int dif = 0, mindif = 5021307000;

    int a, b, c, i, j, o, k, detcted_num, saat = 0;
    int w, h;
    char p[100];

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
            readBMP(p, &w, &h, detect);
            for (j = 0; j <= 9; j++)
            {
                sprintf(p, "fixedlearned%d.bmp", j);
                readBMP(p, &w, &h, learned);
                for (o = 0; o < 887; o++)
                {
                    for (k = 0; k < 740; k++)
                    {
                        dif += abs(learned[o][k][0] - detect[o][k][0]);
                        dif += abs(learned[o][k][1] - detect[o][k][1]);
                        dif += abs(learned[o][k][2] - detect[o][k][2]);
                    }
                }
                //printf("%s\n",p);
                // printf("%d  %lld \n",j,dif);
                if (dif < mindif)
                {
                    mindif = dif;
                    detcted_num = j;
                    //    printf(" %d ",j);
                    //    printf("%lld",dif);
                }
                dif = 0;
            }
            mindif = 5021307000;
            printf("*%d*", detcted_num);
            saat *= 10;
            saat += detcted_num;
        }
    }
    return saat;
}
int abs(int a)
{
    if (a > 0)
    {
        return a;
    }
    else
    {
        return -a;
    }
}