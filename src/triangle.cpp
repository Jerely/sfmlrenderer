#include "triangle.h"
#include "line.h"

void drawTriangle(Triangle& tri, uint8_t* bitmap) {
   plotLine(tri.p[0].x, tri.p[0].y, tri.p[1].x, tri.p[1].y, bitmap); 
   plotLine(tri.p[0].x, tri.p[0].y, tri.p[2].x, tri.p[2].y, bitmap); 
   plotLine(tri.p[1].x, tri.p[1].y, tri.p[2].x, tri.p[2].y, bitmap); 
}

