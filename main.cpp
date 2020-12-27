#include "model.h"
#include <time.h>
#include <iostream>

using namespace std;

int main()
{
    Model M;
    Layer l1(2,4);
    Layer l2(4,2);
    
    M<<l1<<l2;

    Container x(2);
    x.randomize();
    Container y = M.forward(x);
    return 0;
}