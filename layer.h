#pragma once
#include "container.h"

class Layer
{
protected:
    uint nIn, nOut;
    uint threshold;
    Container *kernel;

public:
    Layer(uint, uint);

    Container forward(const Container &);
};