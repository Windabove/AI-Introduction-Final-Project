#include "model.h"
#include <time.h>
using namespace std;

int main()
{
    Model M;
    Layer l1(2,4);
    Layer l2(4,3);
    Layer l3(3,2);
    M.pushLayer(l1);
    M.pushLayer(l2);
    M.pushLayer(l3);

    Container x(10);
    x.randomize();
    auto y = M.forward(x);
    return 0;
}