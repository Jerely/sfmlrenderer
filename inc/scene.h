#pragma once
#include "types.h"
#include "vec3.h"
#include "line.h"
#include "triangle.h"
#include "mtx44.h"
#include <SFML/Graphics.hpp>

extern const int WIDTH;
extern const int HEIGHT;
extern const float FOV;
extern const int SCALEW;
extern const int SCALEH;

struct Scene {
    Mtx44 matProj, matRotY, matRotX, matRotZ, matRXP;
    Mesh cube;
    float thetaX, thetaY, dx, dy, dz;

    void draw(uint8_t*);
    void initCube();
    void populateProj();
    void prepare(Triangle& inTri, Triangle& outTri);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    Scene();
};

void fillPixels(uint8_t* bitmap, Color color);
void MultiplyMatrixVector(Vec3 &i, Vec3 &o, Mtx44 &m);
