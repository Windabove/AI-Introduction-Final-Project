#include "container.h"
#include <iostream>

inline uint offset(uint i)
{
    return size - 1 - i % size;
}

Container::Container() {}

Container::Container(uint _len) : len(_len), content(new block[_len]) {}

Container::Container(const Container &other) : len(other.len)
{
    content = new block[len];
    memcpy(content, other.content, len * sizeof(block));
};

Container::Container(Container &&other) noexcept : len(other.len), content(other.content)
{
    other.content = nullptr;
}

Container::Container(block *&b) : content(b) {}

Container::~Container()
{
    if (content)
    {
        delete[] content;
    }
}

void Container::clear()
{
    memset(content, 0, len);
}

void Container::randomize()
{
    for (int i = 0; i < len; i++)
    {
        content[i] = rand();
    }
}

void Container::writeBit(uint i, bool b)
{
    content[i / size] &= ~(1 << offset(i));
    content[i / size] |= (b << offset(i));
}

void Container::writeEmpty(uint i, bool b)
{
    content[i / size] |= (b << offset(i));
}

void Container::flip(uint i)
{
    content[i / size] ^= (1 << offset(i));
}

uint Container::popcnt()
{
    uint res = 0;
    for (int i = 0; i < len; i++)
    {
        res += __builtin_popcount(content[i]);
    }
    return res;
}

Container Container::operator&(const Container &other)
{
    Container c(len);
    for (int i = 0; i < len; i++)
    {
        c.content[i] = content[i] && other.content[i];
    }
    return c;
};

Container Container::operator|(const Container &other)
{
    Container c(len);
    for (int i = 0; i < len; i++)
    {
        c.content[i] = content[i] || other.content[i];
    }
    return c;
};

Container Container::operator^(const Container &other)
{
    Container c(len);
    for (int i = 0; i < len; i++)
    {
        c.content[i] = content[i] ^ other.content[i];
    }
    return c;
};

Container &Container::operator~()
{
    for (int i = 0; i < len; i++)
    {
        content[i] = ~content[i];
    }
    return *this;
};

bool Container::operator[](uint i)
{
    return content[i / size] & 1 << offset(i) % size;
}

Container &Container::operator()(uint _len)
{
    len = _len;
    content = new block[_len];
    clear();
    return *this;
}

Container &Container::operator=(Container &&other)
{
    if (this == &other)
    {
        throw "Assignment to the same object is not allowed";
    }
    else
    {
        len = other.len;
        content = other.content;
        other.content = nullptr;
        return *this;
    }
}
