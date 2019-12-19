#pragma once
#include "triangle.h"
#include <functional>

struct Rasterizer;
typedef std::function<void(const Rasterizer&, const Triangle&, float, float, Vec4&)> Shader;

enum RenderingMode
    {
     WIREFRAME, PHONG, GOURAUD, FLAT
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
	Vec4 dir;
	Vec4 att;
    float range;
	float spot;
};

struct Rasterizer
{
	float exp;
	float brightness;
	void updateLights();
    Material mat;
    Light light0;
    Light light1;
    Light light2;
    Vec4 eyePos; //always (0,0,0) because there is no camera for now (probably ever)
    RenderingMode mode;
    bool perspectiveCorrect;
    uint8_t* bitmap;
    void draw(Triangle&, bool);
    void pixelShader(const Vec4&, const Vec4&, const Vec4&, Vec4&) const;
	void computeLight(const Light& light, const Vec4& pos, const Vec4& normal, const Vec4& toEye, Vec4& ambient, Vec4& diffuse, Vec4& spec) const;
    Rasterizer(uint8_t*);
    void drawWireframe(const Triangle&);
    void findPointInWorld(const Triangle&, float, float, Vec4&);
    void colorize(const Triangle&, Shader);
    void phongShading(const Triangle&, float, float, Vec4&) const;
    void gouraudShading(const Triangle&, float, float, Vec4&) const;
    void flatShading(const Triangle&, Vec4&) const;
	void computeVertexColor(Triangle&) const;
};
