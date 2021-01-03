#include <stdio.h>

int main()
{
    int M, N, m, n, i, j, k, c = 0, o;
    scanf("%d%d", &M, &N);
    int u[M][N];
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            scanf("%d", &u[i][j]);
        }
    }
    scanf("%d%d", &m, &n);
    int h[m][n];
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &h[i][j]);
        }
    }
    for (i = 0; i <= M - m; i++)
    {
        for (j = 0; j <= N - n; j++)
        {
            for (k = 0; k < m; k++)
            {
                for (o = 0; o < n; o++)
                {
                    if (u[i + k][j + o] == h[k][o])
                    {
                        c++;
                    }
                }
            }
            if (c == m * n)
            {
                printf("(%d, %d)",i,j);
                return 0;
            }
            c=0;
        }
    }
    printf("-1");
    return 0;
}