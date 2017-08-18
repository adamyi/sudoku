#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <bitset>
#include <iostream>

#ifdef WIN32 //putchar_unlocked does not exist in windows
#define putchar_unlocked putchar
#endif

typedef __int128 board;

const board ROW_MASK = 0x1FF;
const board BLOCK_MASK = 0x1C0E07;
board COLUMN_MASK = 0x10080; //not constant due to initialization bitwise shift & add

int x[128];
clock_t t1, t2;
board used[9];

const int row_offset[81] = {72, 72, 72, 72, 72, 72, 72, 72, 72,
    63, 63, 63, 63, 63, 63, 63, 63, 63,
    54, 54, 54, 54, 54, 54, 54, 54, 54,
    45, 45, 45, 45, 45, 45, 45, 45, 45,
    36, 36, 36, 36, 36, 36, 36, 36, 36,
    27, 27, 27, 27, 27, 27, 27, 27, 27,
    18, 18, 18, 18, 18, 18, 18, 18, 18,
    9, 9, 9, 9, 9, 9, 9, 9, 9,
    0, 0, 0, 0, 0, 0, 0, 0, 0};

const int column_offset[81] = {0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8};

const int block_offset[81] = {60, 60, 60, 57, 57, 57, 54, 54, 54,
    60, 60, 60, 57, 57, 57, 54, 54, 54,
    60, 60, 60, 57, 57, 57, 54, 54, 54,
    33, 33, 33, 30, 30, 30, 27, 27, 27,
    33, 33, 33, 30, 30, 30, 27, 27, 27,
    33, 33, 33, 30, 30, 30, 27, 27, 27,
    6, 6, 6, 3, 3, 3, 0, 0, 0,
    6, 6, 6, 3, 3, 3, 0, 0, 0,
    6, 6, 6, 3, 3, 3, 0, 0, 0};

int print_appends[81] = {32, 32, 9, 32, 32, 9, 32, 32, 10,
    32, 32, 9, 32, 32, 9, 32, 32, 10,
    32, 32, 9, 32, 32, 9, 32, 32, 0,
    32, 32, 9, 32, 32, 9, 32, 32, 10,
    32, 32, 9, 32, 32, 9, 32, 32, 10,
    32, 32, 9, 32, 32, 9, 32, 32, 0,
    32, 32, 9, 32, 32, 9, 32, 32, 10,
    32, 32, 9, 32, 32, 9, 32, 32, 10,
    32, 32, 9, 32, 32, 9, 32, 32, 10};

void printBoard(board num);

inline void analyzeUsed(int i)
{
    used[x[i]] |= (ROW_MASK << row_offset[i])
        | (COLUMN_MASK >> column_offset[i])
        | (BLOCK_MASK << block_offset[i]);
}

char *revstr(char *str)
{
    char *p1, *p2;

    if (! str || ! *str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}


// For debug purpose.
void printBoard(board num) {
    printf("\n");
    unsigned long long high = num >> 64;
    unsigned long long low = num & 0xFFFFFFFFFFFFFFFFULL;
    printf("high %llu low %llu\n", high, low);
    char tmp[200];
    char prt[500];
    memset(prt, 0, sizeof(prt));
    for (int i = 0 ; i < 17 ; )
    {
        for (int j = 0 ; j < 9 && i < 17 ; ++j, ++i)
        {
            if (i == 0)
                j = 1;
            sprintf(prt, "%s %llu", prt, high & 0x1);
            high >>= 1;
        }
        strcat(prt, "\n");
    }
    printf("%s\n\n", revstr(prt));
}

inline __int128 boardPow(int i)
{
    __int128 ret = 1;
    return ret << (80 - i);
}

void DFS( int i )
{
    if ( i == 81 )
    {
        for (int *i = &x[0], *ending = i + 81, *pr_append = &print_appends[0]; i < ending; ++i, ++pr_append)
        {
            putchar_unlocked(*i + '1');
            if (*pr_append == 0)
            {
                putchar_unlocked(10);
                putchar_unlocked(10);
            } else
                putchar_unlocked(*pr_append);
        }
        t2 = clock();
        float diff = ((float)(t2 - t1) / 1000000.0F ) * 1000;
        printf("\nUsed time: %f milliseconds.\n", diff);
        exit(0);
    }
    if ( x[i] != -1 )
    {
        DFS(i + 1);
        return;
    }
    board *cur = &used[0];
    for ( int k = 0 ; k < 9 ; ++k, ++cur )
    {
        if (((*cur) & boardPow(i)) == 0)
        {
            x[i] = k;
            board tmp[9];
            memcpy(tmp, used, sizeof(used));
            analyzeUsed(i);
            DFS(i + 1);
            memcpy(used, tmp, sizeof(used));
            x[i] = -1;
        }
    }
}

inline int getNumber(char buf)
{
    if (buf >= '0' && buf <= '9')
        return buf - '1';
    if (buf == '?' || buf == '.')
        return -1;
    return -2;
}

int main(int argc, const char *argv[])
{
    COLUMN_MASK <<= 64;
    COLUMN_MASK += 0x4020100804020100ULL;
    memset(x, -1, sizeof(x));
    char buffer;
    for ( int *i = &x[0], *ending = i + 81 ; i < ending ; ++i )
        for(fread(&buffer, sizeof(char), 1, stdin); (*i = getNumber(buffer)) == -2; fread(&buffer, sizeof(char), 1, stdin));
    putchar_unlocked('\n');
    t1 = clock();
    for (int i = 0 ; i < 81 ; ++i)
        analyzeUsed(i);
    DFS(0);
    printf("Solution not found.");
    return -2;
}
