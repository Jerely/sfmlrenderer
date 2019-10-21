#pragma once
#include "vec4.h"
#include "color.h"

struct Vertex {
    Vec4 lPos;
    Vec4 p;
    Vec4 wPos;
    Color color;
    Vertex(const Vec4&, Color);
    Vertex();
};
