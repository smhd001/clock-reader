#include <stdio.h>
#include <bmpio.h>
#include "myheder.h"

unsigned char pic[2000][2000][3];
unsigned char tmp[2000][2000][3];
extern int c ;

int i_tasefid  (int jmin, int jmax, int imin, int imax);
int j_tasefid  (int jmin, int jmax, int imin, int imax);
int i_tasiah   (int jmin, int jmax, int imin, int imax);
int j_tasiah   (int jmin, int jmax, int imin, int imax);
int i_tasiahp  (int jmin, int jmax, int imin, int imax);
int j_tasiahp  (int jmin, int jmax, int imin, int imax);
void cparry    (int jmin, int jmax, int imin, int imax);
int hazfehashie(int jmin, int jmax, int imin, int imax);
int sefidi     (int i,    int j);

void crop (char p[100])
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
        imin = i_tasiah (jmin + 1, width, imin + 1, height);
        imax = i_tasefid(jmin + 1, width, imin + 1, height);
        jmin = j_tasiah (jmin + 1, width, imin + 1, height);
        jmax = j_tasefid(jmin + 1, width, imin + 1, height);

        if (imax == -1 || imin == -1 || jmax == -1 || jmin == -1)
        {
            break;
        }

        while (jmin != -1 && jmax != -1)
        {
            hazfehashie(jmin, jmax, imin, imax);
            jmin = jmax;
            jmin = j_tasiah (jmin + 1, width, imin + 1, height);
            jmax = j_tasefid(jmin + 1, width, imin + 1, height);
        }
        imin = imax;
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
    char name[10];
    //extern int c;
    cparry(  j_tasiah(jmin, jmax, imin, imax),  j_tasiahp(jmin, jmax, imin, imax), i_tasiah(jmin, jmax, imin, imax), i_tasiahp(jmin, jmax, imin, imax));
    int x = -j_tasiah(jmin, jmax, imin, imax) + j_tasiahp(jmin, jmax, imin, imax);
    int y = -i_tasiah(jmin, jmax, imin, imax) + i_tasiahp(jmin, jmax, imin, imax);
    sprintf(name, "out%d.bmp", c);
    //c++;
    saveBMP(tmp, x + 1, y + 1, name);
    return 0;
}

unsigned char out[2000][2000][3];;

void xbozorg(double nesbat, int nwidth, int height);
void ybozorg(double nesbat, int nwidth, int nheight);

void resize (char p[100],int nwidth,int nheight)
{
    
    //scanf("%99s", p);
    char name [100];
    int i, j;
    int width, height ;
    readBMP(p, &width, &height, pic);
    //scanf("%d%d", &, &);
    double x_nesbat = nwidth * 1.0 / width;
    double y_nesbat = nheight * 1.0 / height;
    xbozorg(x_nesbat, nwidth, height);
    ybozorg(y_nesbat, nwidth, nheight);
    sprintf(name,"outre%d.bmp",c);
    saveBMP(out, nwidth, nheight, name);
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
