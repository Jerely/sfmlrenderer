#pragma once
#include "types.h"
#include <cmath>

extern const int WIDTH;
extern const int HEIGHT;

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

void plotLineLow(int x0, int y0, int x1, int y1, uint8_t* bitmap);
void plotLineHigh(int x0, int y0, int x1, int y1, uint8_t* bitmap);
void plotLine(int x0, int y0, int x1, int y1, uint8_t* bitmap);

inline void plotLine(float fx0, float fy0, float fx1, float fy1, uint8_t* bitmap) {
    int x0 = round(fx0 * HEIGHT);
    int x1 = round(fx1 * HEIGHT);
    int y0 = round((1-fy0) * WIDTH);
    int y1 = round((1-fy1) * WIDTH);
    plotLine(x0, y0, x1, y1, bitmap);
}
