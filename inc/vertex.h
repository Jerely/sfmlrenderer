#pragma once
#include "vec3.h"
#include "color.h"

struct Vertex {
    Vec3 p;
    Color color;
    Vertex(const Vec3& p, Color color);
    Vertex();
};
