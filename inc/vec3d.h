#pragma once
#include <vector>
using namespace std;

struct Vec3 {
    float x, y, z;
};

struct Triangle {
    Vec3 p[3];
};

struct Mesh {
    vector<Triangle> tris;
};

struct Mtx44 {
    float m[4][4];
};
