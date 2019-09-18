#pragma once
#include "types.h"
#include "vec3d.h"
#include "line.h"
#include <SFML/Graphics.hpp>

extern const int WIDTH;
extern const int HEIGHT;
extern const float FOV;
extern const int SCALEW;
extern const int SCALEH;

struct Scene {
    Mtx44 matProj, matRotZ, matRotX;
    Mesh cube;
    float fTheta;

    void draw(sf::RenderWindow&, uint8_t*);
    void initCube();
    void populateProj();
    void update(float);
    void prepare(Triangle& inTri, Triangle& triProjected);
    Scene();
};

void drawTriangle(uint8_t* bitmap, Triangle& tri, Color color);
void fillPixels(uint8_t* bitmap, Color color);
void MultiplyMatrixVector(Vec3 &i, Vec3 &o, Mtx44 &m);
