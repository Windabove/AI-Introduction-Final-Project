#include <stdlib.h>
#include <string.h>
#include <time.h>

#define block int
#define size 32

inline uint offset(uint i)
{
    return size - 1 - i % size;
}

class Container
{
protected:
    block *content;
    uint len;
    bool initialized;

public:
    Container();
    ~Container();

    void init(uint, bool);
    void Clear();
    void Randomize();
    void Load(block *);
    block ReadBlock(uint i);
    void WriteBlock(uint i, block);
    void WriteBit(uint, bool);
    void WriteEmptyBit(uint, bool);
    void Flip(uint);
    uint Popcnt();

    Container operator&(const Container &);
    Container operator|(const Container &);
    Container operator^(const Container &);
    Container operator~();
    bool operator[](uint);
    void operator=(const Container &);
};

Container::Container()
{
    this->initialized = false;
}

Container::~Container()
{
    delete[] this->content;
}

void Container::Clear()
{
    memset(this->content, 0, this->len);
}

void Container::init(uint len, bool initRand = false)
{
    this->len = len;
    this->content = new block[len];
    initRand ? Randomize() : Clear();

    this->initialized = true;
}

void Container::Randomize()
{
    for (int i = 0; i < this->len; i++)
    {
        this->content[i] = rand();
    }
}

void Container::Load(block *ptr)
{
    this->content = ptr;
}

block Container::ReadBlock(uint i)
{
    return this->content[i];
}

void Container::WriteBlock(uint i, block val)
{
    this->content[i] = val;
}

void Container::WriteBit(uint i, bool b)
{
    this->content[i / size] &= ~(1 << offset(i));
    this->content[i / size] |= (b << offset(i));
}

void Container::WriteEmptyBit(uint i, bool b)
{
    this->content[i / size] |= (b << offset(i));
}

void Container::Flip(uint i)
{
    this->content[i / size] ^= (1 << offset(i));
}

uint Container::Popcnt()
{
    uint res = 0;
    for (int i = 0; i < this->len; i++)
    {
        res += __builtin_popcount(this->content[i]);
    }
    return res;
}

Container Container::operator&(const Container &other)
{
    Container container;
    container.init(this->len);

    for (int i = 0; i < this->len; i++)
    {
        container.WriteBlock(i, this->content[i] && other.content[i]);
    }
    return container;
}

Container Container::operator|(const Container &other)
{
    Container container;
    container.init(this->len);

    for (int i = 0; i < this->len; i++)
    {
        container.WriteBlock(i, this->content[i] || other.content[i]);
    }
    return container;
}

Container Container::operator~()
{
    Container container;
    container.init(this->len);
    for (int i = 0; i < this->len; i++)
    {
        container.WriteBlock(i, ~this->content[i]);
    }
    return container;
}

Container Container::operator^(const Container &other)
{
    Container container;
    container.init(this->len);

    for (int i = 0; i < this->len; i++)
    {
        container.WriteBlock(i, this->content[i] ^ other.content[i]);
    }
    return container;
}

bool Container::operator[](uint i)
{
    return this->content[i / size] & 1 << offset(i) % size;
}

void Container::operator=(const Container &other)
{
    memcpy(this->content,other.content,this->len);
    this->len = other.len;
}

class Layer
{
protected:
    uint nIn, nOut;
    uint threshold;
    Container *kernel;

public:
    Layer(uint, uint, bool);

    Container Forward(Container &);
};

Layer::Layer(uint nIn, uint nOut, bool initRand = true)
{
    this->nIn = nIn;
    this->nOut = nOut;
    this->threshold = size * nIn / 2;
    this->kernel = new Container[nOut * size];

    for (int i = 0; i < size * nOut; i++)
    {
        this->kernel[i].init(nIn, initRand);
    }
}

Container Layer::Forward(Container &x)
{
    Container container;
    container.init(this->nOut);
    for (int i = 0; i < size * this->nOut; i++)
    {
        container.WriteEmptyBit(i, (x ^ this->kernel[i]).Popcnt() > threshold);
    }
    return container;
}

int main()
{
    time_t t;
    srand((uint)time(&t));

    Container x,y;
    x.init(1000, true);
    y.init(1000);
    Layer layer(1000, 1000);
    y = layer.Forward(x);

    return 1;
}