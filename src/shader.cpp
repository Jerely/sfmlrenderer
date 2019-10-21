#include "rasterizer.h"

void PhongShader::operator()(const Rasterizer& r, const Triangle& tri, float s, float t, Vec4& vecColor)
{
    r.phongShading(tri, s, t, vecColor);
}

void FalseShader::operator()(const Rasterizer& r, const Triangle& tri, float s, float t, Vec4& vecColor)
{
    r.falseShading(tri, s, t, vecColor);
}
