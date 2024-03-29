#pragma once
#include "types.h"
#include "vec3.h"

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;	
    uint8_t a;
    Color(uint8_t, uint8_t, uint8_t, uint8_t);
    Color();
    inline uint32_t toU32() { return (a << 24) | (b << 16) | (g << 8) | r; }
    Vec3 toVec3();
};

const Color WHI = {255, 255, 255, 255};
const Color BLA = {0, 0, 0, 255};
const Color RED = {255, 0, 0, 255};
const Color GRE = {0, 255, 0, 255};
const Color NAV = {0, 0, 255, 255};
const Color YEL = {255, 255, 0, 255};
const Color PUR = {255, 0, 255, 255};
const Color BLU = {0, 255, 255, 255}; 

float intToFloat(int imin, int imax, float fmin, float fmax, int i);
int floatToInt(int imin, int imax, float fmin, float fmax, float f);

inline float byteToNorm(uint8_t i) {
    return intToFloat(0, 255, 0, 1.0f, i);
}
