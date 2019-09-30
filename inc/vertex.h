#pragma once
#include "vec4.h"
#include "color.h"

struct Vertex {
    Vec4 p;
    Color color;
    Vertex(const Vec4& p, Color color);
    Vertex();
};
