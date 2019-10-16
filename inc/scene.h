#pragma once
#include "types.h"
#include "vec4.h"
#include "line.h"
#include "triangle.h"
#include "mtx44.h"
#include "camera.h"
#include <SFML/Graphics.hpp>

extern const int WIDTH;
extern const int HEIGHT;
extern const float FOV;
extern const int SCALEW;
extern const int SCALEH;

struct Scene {
    Mtx44 matProj,
          matScale,
          matTranslate,
          matRotY,
          matRotX,
          matRotZ,
          matCamera,
          matSRT;

    Mesh cube,
        square; //for testing
    float thetaX, thetaY, thetaZ, dx, dy, dz; 
    RenderingMode mode;

    Camera camera;

    void draw(uint8_t*);
    void drawMesh(const Mesh& mesh, uint8_t* bitmap);
    void projectManually(const Vec4&, Vec4&); //for debug
    void initSquare(); //for debug
    void initCube();
    void project();
    void rotateX(float angle);
    Mtx44 rotateY(float angle);
    void rotateZ(float angle);
    void translate(float x, float y, float z);
    void scale(float q);
    void update();
    Scene();
};

void fillPixels(uint8_t* bitmap, Color color);
