#include "layer.h"

Layer::Layer(){}

Layer::Layer(uint _nIn, uint _nOut) : nIn(_nIn), nOut(_nOut)
{
    threshold = size * nIn / 2;
    kernel = new Container[nOut * size];

    for (int i = 0; i < size * nOut; i++)
    {
        kernel[i](nIn).randomize();
    }
}

Layer::Layer(const Layer &l){}

Layer::~Layer()
{
    if (kernel)
        delete[] kernel;
}

Container Layer::forward(const Container &x)
{
    Container c(nOut);
    for (int i = 0; i < size * nOut; i++)
    {
        c.writeEmpty(i, (kernel[i] ^ x).popcnt() > threshold);
    }
    return c;
}