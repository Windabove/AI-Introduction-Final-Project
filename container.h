#pragma once

#include <stdlib.h>
#include <string.h>
#include <utility>

#define size 32
typedef int block;

class Layer;

class Container
{
protected:
    uint len;
    block *content;

    friend Layer;

public:
    Container();
    Container(uint);
    Container(Container &&);
    Container(const Container &) = delete;
    Container(block *&);

    ~Container();

    void clear();
    void randomize();

    void writeBit(uint, bool);
    void writeEmpty(uint, bool);
    void flip(uint);

    uint popcnt();

    Container operator&(const Container &);
    Container operator|(const Container &);
    Container operator^(const Container &);

    Container &operator~();
    
    bool operator[](uint);

    Container& operator()(uint);
};