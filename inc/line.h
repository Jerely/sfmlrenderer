#pragma once
#include "types.h"

extern const int WIDTH;

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    Color(uint8_t, uint8_t, uint8_t, uint8_t);
    inline uint32_t toU32() { return (r << 24) | (g << 16) | (b << 8) | a; }
};

const Color WHITE = {255, 255, 255, 255};
const Color BLACK = {0, 0, 0, 255};
const Color RED = {255, 0, 0, 255};

inline void setPixel(uint8_t* bitmap, uint32_t x, uint32_t y, Color color) {
    ((uint32_t*)bitmap)[x+y*WIDTH] = color.toU32();
}

void line(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint8_t* bitmap, Color color);
