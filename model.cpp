#include "model.h"

using namespace std;

Model::Model(){}

Model::~Model()
{
    layers.clear();
}

Model &Model::pushLayer(const Layer& layer)
{
    if (port == layer.nIn||layers.size()==0)
    {
        layers.push_back(layer);
        port = layer.nOut;
        return *this;
    }
}

Container Model::forward(const Container &x)noexcept
{
    Container y = x;
    for (auto l:layers){
        y = l.forward(y);
    }
    return y;
}