#pragma once
#include "triangle.h"

enum RenderingMode {
    WIREFRAME, COLORED
};

struct Rasterizer
{
    RenderingMode mode;
    bool perspectiveCorrect;
    uint8_t* bitmap;
    void draw(const Triangle&);
    void determineColor(const Triangle&, float s, float t, Color& color);
    Rasterizer(uint8_t*);
};
