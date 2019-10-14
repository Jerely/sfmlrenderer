#pragma once
#include "types.h"
#include "vec4.h"
#include "line.h"
#include "triangle.h"
#include "mtx44.h"
#include <SFML/Graphics.hpp>

extern const int WIDTH;
extern const int HEIGHT;
extern const float FOV;
extern const int SCALEW;
extern const int SCALEH;

enum ControlMode {
                  CAMERA,
                  OBJECT
};

struct Scene {
    Mtx44 matProj,
          matScale,
          matTranslate,
          matRotY,
          matRotX,
          matRotZ,
          matCamera,
          matView,
          matSRT;

    Vec4 camera, lookDir;

    Mesh cube;
    float thetaX, thetaY, thetaZ, dx, dy, dz, camAngleY;
    RenderingMode mode;

    ControlMode control;

    void draw(uint8_t*);
    void initCube();
    void project();
    void rotateX(float angle);
    Mtx44 rotateY(float angle);
    void rotateZ(float angle);
    void translate(float x, float y, float z);
    void scale(float q);
    void prepareCamera();
    void prepareView();
    void update();
    void pointAt(Vec4& pos, Vec4& target, Vec4&  up);
    Scene();
};

void fillPixels(uint8_t* bitmap, Color color);
