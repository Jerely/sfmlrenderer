#pragma once
#include "triangle.h"

enum RenderingMode
    {
     WIREFRAME, COLORED, PHONG
    };

struct Material
{
    Vec4 ambient;
    Vec4 diffuse;
    Vec4 spec;
};

struct Light
{
    Vec4 ambient;
    Vec4 diffuse;
    Vec4 spec;
    Vec4 pos;
    float range;
};

struct Rasterizer
{
    Material mat;
    Light light;
    Vec4 eyePos; //always (0,0,0) because there is no camera for now (probably ever)
    RenderingMode mode;
    bool perspectiveCorrect;
    uint8_t* bitmap;
    void draw(const Triangle&);
    void determineColor(const Triangle&, float s, float t, Color& color);
    void computeLight(const Vec4&, const Vec4&, const Vec4&, Vec4&);
    Rasterizer(uint8_t*);
    void drawWireframe(const Triangle&);
    void drawColored(const Triangle&);
    void drawPhong(const Triangle&);
};
