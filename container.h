#pragma once

#include <stdlib.h>
#include <string.h>
#include <utility>

const int size = 32;
typedef int block;

class Layer;
class Model;

class Container
{
protected:
    uint len;
    block *content;

    friend Layer;
    friend Model;

public:
    Container();
    Container(uint);
    Container(const Container&);
    Container(Container &&) noexcept;
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

    Container &operator()(uint);
    Container &operator=(Container &&);
};