#pragma once

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    Color(uint8_t, uint8_t, uint8_t, uint8_t);
    inline uint32_t toU32() { return (r << 24) | (g << 16) | (b << 8) | a; }
};

const Color WHITE  = {255, 255, 255, 255};
const Color BLACK  = {0, 0, 0, 255};
const Color RED    = {255, 0, 0, 255};
const Color GREEN  = {0, 255, 0, 255};
const Color NAVY   = {0, 0, 255, 255};
const Color YELLOW = {255, 255, 0, 255};
const Color PURPLE = {255, 0, 255, 255};
const Color BLUE   = {0, 255, 255, 255}; 

