#pragma once
#include "vertex.h"
#include <SFML/Graphics.hpp>
extern sf::RenderWindow* pWindow;

extern bool perspectiveCorrect;

enum RenderingMode {
    WIREFRAME, COLORED
};

struct Triangle {
    Vertex v[3];
    Vec4 norm;
    Triangle();
    Triangle(Vertex v0, Vertex v1, Vertex v2);
    void computeNorm();
    void draw(RenderingMode mode, uint8_t* bitmap);
    void getBoundaries(float& minX, float& minY, float& maxX, float& maxY);
    void intBoundaries(int& iMinX, int& iMinY, int& iMaxX, int& iMaxY);
    bool pointIsIn(float s, float t);
    void determineColor(float s, float t, Color& color);
    void findBarycentricCoord(const Vec4& p, float& s, float& t);
};




