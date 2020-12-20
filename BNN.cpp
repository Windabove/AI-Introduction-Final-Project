#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define char32 unsigned int

const int layerN = 3;

void initRand()
{
    time_t t;
    srand((unsigned)time(&t));
}

char32 kernel(char32 x, char32 w[][32])
{
    char32 res = x;
    for (int i = 0; i < layerN; i++)
    {
        char32 tmp = 0;
        for (int j = 0; j < 32; j++)
            tmp = tmp << 1 | (__builtin_popcount(w[i][j] ^ res) > 16);

        res = tmp;
    }
    return res;
}

int err(char32 x[], char32 y[], char32 w[][32])
{
    int res = 0;

    for (int i = 0; i < 10; i++)
    {
        res += __builtin_popcount(y[i] ^ kernel(x[i], w));
    }

    return res;
}

int main()
{
    initRand();

    const int N = 1000000;
    char32 w[layerN][32];
    for (int i = 0; i < layerN; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            w[i][j] = rand();
        }
    }

    char32 f[10], l[10];
    for (int i = 0; i < 10; i++)
        f[i] = rand();
    for (int i = 0; i < 10; i++)
        l[i] = rand();

    printf("initial error:%d\n", err(f, l, w));

    clock_t t0, t1;
    t0 = clock();

    for (int r = 0; r < N; r++)
    {
        unsigned i = rand() % layerN;
        unsigned j = rand() % 32;
        char32 k = 0x1 << (rand() % 32);

        int a = err(f, l, w);
        w[i][j] ^= k;
        int b = err(f, l, w);
        if (a < b)
            w[i][j] ^= k;
    }

    t1 = clock();

    printf("final error:%d\n", err(f, l, w));
    printf("time spend:%d s\n", (t1 - t0) / CLOCKS_PER_SEC);
    printf("per loop:%f ms\n", (t1 - t0) * 1.0 / N);
    return 1;
}