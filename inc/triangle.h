#pragma once
#include "vertex.h"
#include <SFML/Graphics.hpp>

struct Triangle {
    Vertex v[3];
    Vec4 norm;
    Triangle();
    Triangle(Vertex v0, Vertex v1, Vertex v2);
    void computeNorm();
    void getBoundaries(float& minX, float& minY, float& maxX, float& maxY) const;
    void intBoundaries(int& iMinX, int& iMinY, int& iMaxX, int& iMaxY) const;
    bool pointIsIn(float s, float t) const;
    void findBarycentricCoord(const Vec4& p, float& s, float& t) const;
};




