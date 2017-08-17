#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int x[9][9];
bool a[9][9][9];
clock_t t1, t2;

void generateA()
{
    bool tmp[9];
    for ( int i = 0 ; i < 9 ; i++ )
    {
        memset(tmp, 0, sizeof(tmp));
        for ( int j = 0 ; j < 9 ; j++ )
            if ( x[i][j] != -1 )
                tmp[x[i][j]] = true;
        for ( int j = 0 ; j < 9 ; j++ )
            if ( tmp[j] )
                for ( int k = 0 ; k < 9 ; k++ )
                    a[i][k][j] = true;
    }
    for ( int i = 0 ; i < 9 ; i++ )
    {
        memset(tmp, 0, sizeof(tmp));
        for ( int j = 0 ; j < 9 ; j++ )
            if ( x[j][i] != -1 )
                tmp[x[j][i]] = true;
        for ( int j = 0 ; j < 9 ; j++ )
            if ( tmp[j] )
                for ( int k = 0 ; k < 9 ; k++ )
                    a[k][i][j] = true;
    }
    for ( int i = 0 ; i < 7 ; i += 3 )
    {
        for ( int j = 0 ; j < 7 ; j += 3 )
        {
            memset(tmp, 0, sizeof(tmp));
            for ( int k = 0 ; k < 3 ; k++ )
                for ( int l = 0 ; l < 3 ; l++ )
                    if ( x[i + l][j + k] != -1 )
                        tmp[x[i + l][j + k]] = true;
            for ( int k = 0 ; k < 9 ; k++ )
                if ( tmp[k] )
                    for ( int l = 0 ; l < 3 ; l++ )
                        for ( int m = 0 ; m < 3 ; m++ )
                            a[i + m][j + l][k] = true;
        }
    }
}

void generateAChanges(int m, int n)
{
    bool tmp[9];

    int k = x[m][n];
    for ( int i = 0 ; i < 9 ; i++ )
        a[m][i][k] = true;
    for ( int i = 0 ; i < 9 ; i++ )
        a[i][n][k] = true;
    int lu_x = (m - m % 3), lu_y = (n - n % 3);
    for ( int i = 0 ; i < 3 ; i++ )
        for ( int j = 0 ; j < 3 ; j++ )
            a[i + lu_x][j + lu_y][k] = true;
}

void DFS( int i, int j )
{
    if ( i == 9 )
    {
        for ( int k = 0 ; k < 9 ; k++ )
        {
            printf("%d", x[k][0] + 1);
            for ( int l = 1 ; l < 9 ; l++ )
            {
                printf(" %d", x[k][l] + 1);
            }
            printf("\n");
        }
	t2 = clock();
	float diff = ((float)(t2 - t1) / 1000000.0F ) * 1000;
	printf("\nUsed time: %f milliseconds.\n", diff);
        exit(0);
    }
    if ( x[i][j] != -1 )
    {
        if ( j < 8 )
            DFS(i, j + 1);
        else
            DFS(i + 1, 0);
        return;
    }
    for ( int k = 0 ; k < 9 ; k++ )
    {
        if (a[i][j][k] == false)
        {
            x[i][j] = k;
            bool tmp[9][9][9];
            memcpy(tmp, a, sizeof(a));
            generateAChanges(i, j);
            if ( j < 8 )
                DFS(i, j + 1);
            else
                DFS(i + 1, 0);
            memcpy(a, tmp, sizeof(a));
            x[i][j] = -1;
        }
    }
}

int main(int argc, const char *argv[])
{
    memset(x, -1, sizeof(x));
    memset(a, 0, sizeof(a));
    for ( int i = 0 ; i < 9 ; i++ )
    {
        for ( int j = 0 ; j < 9 ; j++ )
        {
            scanf("%d", &x[i][j]);
            x[i][j]--;
        }
    }
    t1 = clock();
    generateA();
    DFS(0, 0);
    return 0;
}
