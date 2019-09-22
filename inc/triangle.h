#pragma once
#include "vertex.h"

enum RenderingMode {
    WIREFRAME, TEST
};

struct Triangle {
    Vertex v[3];
    Vec3 norm;
    Triangle();
    Triangle(Vertex v0, Vertex v1, Vertex v2);
    void computeNorm();
    void draw(RenderingMode mode, uint8_t* bitmap);
};

struct Mesh {
    vector<Triangle> tris;
};

