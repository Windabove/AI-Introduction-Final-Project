#include "model.h"
#include <time.h>
#include <iostream>

using namespace std;

int main()
{
    try
    {
        Model M;
        Layer l1(1000, 1000);
        Layer l2(1000, 1000);
        Layer l3(1000, 1000);


        M << l1 << l2 << l3;

        Container x(1000);
        x.randomize();

        clock_t t0, t1;
        t0 = clock();
        Container y = M.forward(x);

        t1 = clock();

        cout << (t1 - t0) * 1000 / CLOCKS_PER_SEC << "ms" << endl;
        return 0;
    }
    catch (const char *e)
    {
        cout << e << endl;
    }
}