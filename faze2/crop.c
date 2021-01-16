#include <stdio.h>
#include <bmpio.h>

unsigned char pic[2000][2000][3];
unsigned char tmp[2000][2000][3];
int c = 1;

int i_tasefid  (int jmin, int jmax, int imin, int imax);
int j_tasefid  (int jmin, int jmax, int imin, int imax);
int i_tasiah   (int jmin, int jmax, int imin, int imax);
int j_tasiah   (int jmin, int jmax, int imin, int imax);
int i_tasiahp  (int jmin, int jmax, int imin, int imax);
int j_tasiahp  (int jmin, int jmax, int imin, int imax);
void cparry    (int jmin, int jmax, int imin, int imax);
int hazfehashie(int jmin, int jmax, int imin, int imax);
int sefidi     (int i,    int j);

int main()
{
    char p[100];
    scanf("%99s", p);
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

    return 0;
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
    int i, j, c = 1;
    for (i = imin; i < imax; i++)
    {
        for (j = jmin; j < jmax; j++)
        {
            if (!sefidi(i, j))
            {
                c = 0;
                break;
            }
        }
        if (c)
        {
            return i;
        }
        c = 1;
    }
    return -1;
}
int j_tasefid(int jmin, int jmax, int imin, int imax)
{
    int i, j, c;
    for (j = jmin; j < jmax; j++)
    {
        for (i = imin; i < imax; i++)
        {
            if (!sefidi(i, j))
            {
                c = 0;
                break;
            }
        }
        if (c)
        {
            return j;
        }
        c = 1;
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
    cparry(  j_tasiah(jmin, jmax, imin, imax),  j_tasiahp(jmin, jmax, imin, imax), i_tasiah(jmin, jmax, imin, imax), i_tasiahp(jmin, jmax, imin, imax));
    int x = -j_tasiah(jmin, jmax, imin, imax) + j_tasiahp(jmin, jmax, imin, imax);
    int y = -i_tasiah(jmin, jmax, imin, imax) + i_tasiahp(jmin, jmax, imin, imax);
    sprintf(name, "out%d.bmp", c);
    c++;
    saveBMP(tmp, x + 1, y + 1, name);
    return 0;
}
