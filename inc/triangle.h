#pragma once
#include "vec3.h"

struct Triangle {
    Vec3 p[3];
};

struct Mesh {
    vector<Triangle> tris;
};


void drawTriangle(Triangle& tri, uint8_t* bitmap);
