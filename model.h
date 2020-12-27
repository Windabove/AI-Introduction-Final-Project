#pragma once
#include "layer.h"
#include <vector>

using namespace std;
class Model{
    protected:
    uint port;
    vector<Layer*> layers;

    public:
    Model();
    ~Model();

    Model& operator<<(Layer& layer);
    Container forward(const Container&)noexcept;
};