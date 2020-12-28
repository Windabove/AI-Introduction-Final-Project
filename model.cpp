#include "model.h"

using namespace std;

Model::Model() {}

Model::~Model()
{
    layers.clear();
}

Model &Model::operator<<(Layer &layer)
{
    if (layers.size() == 0)
    {
        layers.push_back(&layer);
        portIn = layer.nIn;
        portOut = layer.nOut;
        return *this;
    }
    else if (portOut == layer.nIn)
    {
        layers.push_back(&layer);
        portOut = layer.nOut;
        return *this;
    }
    else if (portOut != layer.nIn)
    {
        throw "Invalid nIn";
    }
}

Container Model::forward(const Container &x)
{
    if (x.len != portIn)
    {
        throw "Invalid length of input vector";
    }
    else
    {
        Container tmp(x);
        for (auto l : layers)
        {
            tmp = move(l->forward(tmp));
        }
        return tmp;
    }
}