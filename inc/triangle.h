#pragma once
#include "vec3.h"

struct Triangle {
    Vec3 p[3];
    Vec3 norm;
    Triangle();
    Triangle(Vec3 const &p0, Vec3 const &p1, Vec3 const &p2);
    void computeNorm();
};

struct Mesh {
    vector<Triangle> tris;
};


void drawTriangle(Triangle& tri, uint8_t* bitmap);
