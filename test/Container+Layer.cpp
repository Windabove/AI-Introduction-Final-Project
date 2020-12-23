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

public:
    Container(uint, bool);
    ~Container();

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
};

Container::Container(uint len, bool initRand = false)
{
    this->len = len;
    this->content = new block[len];
    initRand ? Randomize() : Clear();
}

Container::~Container()
{
    delete this->content;
}

void Container::Clear()
{
    memset(this->content, 0, this->len);
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
    Container container(this->len);
    for (int i = 0; i < this->len; i++)
    {
        container.WriteBlock(i, this->content[i] && other.content[i]);
    }
    return container;
}

Container Container::operator|(const Container &other)
{
    Container container(this->len);
    for (int i = 0; i < this->len; i++)
    {
        container.WriteBlock(i, this->content[i] || other.content[i]);
    }
    return container;
}

Container Container::operator~()
{
    Container container(this->len);
    for (int i = 0; i < this->len; i++)
    {
        container.WriteBlock(i, ~this->content[i]);
    }
    return container;
}

Container Container::operator^(const Container &other)
{
    Container container(this->len);
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

class Layer
{
protected:
    uint nIn, nOut;
    uint threshold;
    Container **kernel;

public:
    Layer(uint, uint, bool);
    ~Layer();

    Container Forward(Container);
};

Layer::Layer(uint nIn, uint nOut, bool initRand = true)
{
    this->nIn = nIn;
    this->nOut = nOut;
    this->threshold = size * nIn / 2;
    this->kernel = new Container*[nOut*size];

    for (int i = 0; i < size * nOut; i++)
    {
        this->kernel[i] = new Container(nIn, initRand);
    }
}

Layer::~Layer()
{
    free(this->kernel);
}

Container Layer::Forward(Container x)
{
    Container res(this->nOut);
    for (int i = 0; i < size * this->nOut; i++)
    {
        res.WriteEmptyBit(i, (x ^ *this->kernel[i]).Popcnt() > threshold);
    }
    return res;
}

int main()
{
    time_t t;
    srand((uint)time(&t));

    Container x(10,true);
    Layer layer(10, 10);
    Container y = layer.Forward(x);
    return 1;
}