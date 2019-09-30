#include "color.h"

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
    r(r), g(g), b(b), a(a) {};

Color::Color() :
    r(0), g(0), b(0), a(0) {};

float intToFloat(int imin, int imax, float fmin, float fmax, int i) {
    float f = ((float) (i - imin)) / ((float) (imax-imin)); 
    f = (fmax-fmin) * f + fmin;
    f = f > fmax ? fmax : f;
    f = f < fmin ? fmin : f;
    return f;
}


int floatToInt(int imin, int imax, float fmin, float fmax, float f) {
    f = (f-fmin) / (fmax-fmin);
    f = (f * (float)(imax-imin)) + (float) imin;
    int i = (int) round(f);
    i = i > imax ? imax : i;
    i = i < imin ? imin : i;
    return i;
}


Vec4 Color::toVec3() {
    return Vec4(byteToNorm(r), byteToNorm(g), byteToNorm(b));
}
