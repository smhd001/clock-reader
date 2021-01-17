#include <stdio.h>
#include <bmpio.h>

unsigned char pic[2000][2000][3];
unsigned char tmp[2000][2000][3];
unsigned char out[2000][2000][3];;

void xbozorg(double nesbat, int nwidth, int height);
void ybozorg(double nesbat, int nwidth, int nheight);

int main()
{
    char p[100];
    scanf("%99s", p);
    int i, j;
    int width, height, nheight, nwidth;
    readBMP(p, &width, &height, pic);
    scanf("%d%d", &nwidth, &nheight);
    double x_nesbat = nwidth * 1.0 / width;
    double y_nesbat = nheight * 1.0 / height;
    xbozorg(x_nesbat, nwidth, height);
    ybozorg(y_nesbat, nwidth, nheight);
    saveBMP(out, nwidth, nheight, "outre.bmp");
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