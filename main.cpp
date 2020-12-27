#include "layer.h"
#include <time.h>

using namespace std;

int main()
{
    time_t t;
    srand((uint)time(&t));

    Layer l(10, 10);
    Container x(10);
    x.randomize();

    Container y = l.forward(x);
    return 0;
}