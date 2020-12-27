#pragma once
#include "container.h"

class Model;
class Layer
{
protected:
    uint nIn, nOut;
    uint threshold;
    Container *kernel;

    friend Model;

public:
    Layer();
    Layer(uint, uint);
    ~Layer();

    Container forward(const Container &);
};