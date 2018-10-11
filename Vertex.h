#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include <cinttypes>

struct Position3
{
public:
    Position3() : x(0.f), y(0.f), z(0.f) { }
    Position3(float x, float y, float z) : x(x), y(y), z(z) { }
    Position3(const Position3 &pos) : x(pos.x), y(pos.y), z(pos.z) { }
    float x;
    float y;
    float z;
};

struct ColorRGB
{
public:
    ColorRGB() { }
    ColorRGB(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) { }
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct Index3
{
public:
    Index3() : frst(0), scnd(0), thrd(0) { }
    Index3(uint32_t frst, uint32_t scnd, uint32_t thrd) : frst(frst), scnd(scnd), thrd(thrd) { }
    uint32_t frst;
    uint32_t scnd;
    uint32_t thrd;
};

struct Vertex
{
public:
    Vertex() { }
    Vertex(const Position3 &pos) : positions(pos)  {  }

    Position3 positions;
};

#endif //!VERTEX_H
