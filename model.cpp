#include "model.h"

using namespace std;

Model::Model(){}

Model::~Model()
{
    layers.clear();
}

Model& Model::operator<<(Layer& layer)
{
    if (port == layer.nIn||layers.size()==0)
    {
        layers.push_back(&layer);
        port = layer.nOut;
    }else if(port != layer.nIn){
        throw("Invalid port");
    }
}

Container Model::forward(const Container& x)noexcept
{
    Container y(x);
    for (auto l:layers){
        y = l->forward(y);
    }
    return y;
}