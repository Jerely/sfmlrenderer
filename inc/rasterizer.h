#pragma once
#include "triangle.h"

struct Rasterizer;

struct Shader
{
    virtual void operator()(const Rasterizer&, const Triangle&, float, float, Vec4&) = 0;
};

struct PhongShader : public Shader
{
    virtual void operator()(const Rasterizer&, const Triangle&, float, float, Vec4&) override;
};

struct FalseShader : public Shader
{
    virtual void operator()(const Rasterizer&, const Triangle&, float, float, Vec4&) override;
};


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
    void computeLight(const Vec4&, const Vec4&, const Vec4&, Vec4&) const;
    Rasterizer(uint8_t*);
    void drawWireframe(const Triangle&);
    void drawColored(const Triangle&);
    void drawPhong(const Triangle&);
    void findPointInWorld(const Triangle&, float, float, Vec4&);
    void colorize(const Triangle&, Shader& shader);
    void phongShading(const Triangle&, float, float, Vec4&) const;
    void falseShading(const Triangle&, float, float, Vec4&) const;
};
