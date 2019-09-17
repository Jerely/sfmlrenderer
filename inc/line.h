#pragma once

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

extern const int WIDTH;

union Color {
    uint32_t u32color;
    struct U8color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
        void green() { r = 0; g = 255; b = 0; a = 255; }
    };
    U8color u8color;
};

inline void setPixel(uint8_t* bitmap, uint32_t x, uint32_t y, Color color) {
    ((uint32_t*)bitmap)[x+y*WIDTH] = color.u32color;
}

void line(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint8_t* bitmap, Color color);
