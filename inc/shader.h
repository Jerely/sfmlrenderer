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
