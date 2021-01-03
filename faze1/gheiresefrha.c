#include <stdio.h>
int bret(int i, int a);
int main()
{
    int a, b, c=0, m, n, imn = 0, imx , jmn = 0, jmx , i, j;
    scanf("%d%d", &m, &n);
    int u[m][n];
    imx=m-1;
    jmx=n-1;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &u[i][j]);
        }
    }
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (u[i][j] != 0)
            {
                c++;
            }
        }
        if (!c)
        {
            imn = i + 1;
        }
        else
        {
            break;
        }
    }
    c=0;
    for (i = m - 1; i > imn; i--)
    {
        for (j = 0; j < n; j++)
        {
            if (u[i][j] != 0)
            {
                c++;
            }
        }
        if (!c)
        {
            imx = i - 1;
        }
        else
        {
            break;
        }
    }
    c=0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (u[j][i] != 0)
            {
                c++;
            }
        }
        if (!c)
        {
            jmn = i + 1;
        }
        else
        {
            break;
        }
    }
    c=0;
    for (i = n - 1; i > jmn; i--)
    {
        for (j = 0; j < m; j++)
        {
            if (u[j][i] != 0)
            {
                c++;
            }
        }
        if (!c)
        {
            jmx = i - 1;
        }
        else
        {
            break;
        }
    }
    for (i = imn; i <= imx; i++)
    {
        for (j = jmn; j <= jmx; j++)
        {
            printf("%d ", u[i][j]);
        }
        printf("\n");
    }
}