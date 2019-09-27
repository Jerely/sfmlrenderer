#include "line.h"
#define abs(x) ((x) > 0 ? (x) : -(x))
const Color WIRE_COLOR = WHI;

void plotLineLow(int x0, int y0, int x1, int y1, uint8_t* bitmap) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0) {
      yi = -1;
      dy = -dy;
    }
    int D = 2*dy - dx;
    int y = y0;
    for(int x = x0; x <= x1; ++x) {
        setPixel(bitmap, x, y, WIRE_COLOR);
        if(D > 0) {
            y = y + yi;
            D = D - 2*dx;
        }
      D += 2*dy;
    }
}

void plotLineHigh(int x0, int y0, int x1, int y1, uint8_t* bitmap) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if(dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int D = 2*dx - dy;
    int x = x0;
    for(int y = y0; y <= y1; ++y) {
        setPixel(bitmap, x, y, WIRE_COLOR);
        if(D > 0) {
            x += xi;
            D -= 2*dy;
        }
        D += 2*dx;
    }
}

void plotLine(int x0, int y0, int x1, int y1, uint8_t* bitmap) {
    if(abs(y1 - y0) < abs(x1 - x0)) {
        if(x0 > x1) {
            plotLineLow(x1, y1, x0, y0, bitmap);
        }
        else {
            plotLineLow(x0, y0, x1, y1, bitmap);
        }
    }
    else {
        if(y0 > y1) {
            plotLineHigh(x1, y1, x0, y0, bitmap);
        }
        else {
            plotLineHigh(x0, y0, x1, y1, bitmap);
        }
    }
}

