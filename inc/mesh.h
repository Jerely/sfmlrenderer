#pragma once
#include "triangle.h"

struct Mesh {
    std::vector<Triangle> tris;
    Mtx44 matScale,
        matTranslate,
        matRotY,
        matRotX,
        matRotZ,
        matSRT;

    float thetaX,
          thetaY,
          thetaZ,
            scale,
          x,
          y,
          z; 

    void getMatSRT();
    void update();
};

Mesh initSquare(); 
Mesh initCube();
