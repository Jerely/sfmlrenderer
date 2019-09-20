#pragma once
#include "vec3.h"

struct Triangle {
    Vec3 p[3];
    Triangle();
    Triangle(Vec3 const &p0, Vec3 const &p1, Vec3 const &p2);
};

struct Mesh {
    vector<Triangle> tris;
};


void drawTriangle(Triangle& tri, uint8_t* bitmap);
