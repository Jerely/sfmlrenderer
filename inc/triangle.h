#pragma once
#include "vertex.h"

enum RenderingMode {
    WIREFRAME, TEST
};

struct Triangle {
    Vertex v[3];
    Vec3 norm;
    Triangle();
    Triangle(Vertex v0, Vertex v1, Vertex v2);
    void computeNorm();
    void draw(RenderingMode mode, uint8_t* bitmap);
    void getBoundaries(float& minX, float& minY, float& maxX, float& maxY);
    void intBoundaries(int& iMinX, int& iMinY, int& iMaxX, int& iMaxY);
    bool pointIsIn(float s, float t);
    void determineColor(float s, float t, Color& color);
    void findBarycentricCoord(const Vec3& p, float& s, float& t);
};

struct Mesh {
    vector<Triangle> tris;
};



