#pragma once
#include "vec3.h"

enum RenderingMode {
    WIREFRAME, TEST
};

struct Triangle {
    Vec3 p[3];
    Vec3 norm;
    Triangle();
    Triangle(Vec3 const &p0, Vec3 const &p1, Vec3 const &p2);
    void computeNorm();
    void draw(RenderingMode mode, uint8_t* bitmap);
};

struct Mesh {
    vector<Triangle> tris;
};

