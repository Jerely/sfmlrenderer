#include "line.h"

void line(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint8_t* bitmap, Color color) {
    for (uint32_t x=x0; x<=x1; x++) {
        float t = (x-x0)/(float)(x1-x0);
        uint32_t y = y0*(1.-t) + y1*t;
        setPixel(bitmap, x, y, color);
    }
}
