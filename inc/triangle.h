#pragma once
#include "vertex.h"
#include <SFML/Graphics.hpp>

struct BoundSquare
{
    int minX,
        minY,
        maxX,
        maxY;
};

struct Triangle {
    Vertex v[3];
    Vec4 norm;
    Triangle();
    Triangle(Vertex v0, Vertex v1, Vertex v2);
    void computeNorm();
    void getBoundingSquare(BoundSquare&) const;
    bool pointIsIn(float s, float t) const;
    void findBarycentricCoord(const Vec4& p, float& s, float& t) const;
    void interpolateColor(float s, float t, Vec4& vecColor) const;
    void findPointInWorld(float s, float, Vec4&) const;
};




