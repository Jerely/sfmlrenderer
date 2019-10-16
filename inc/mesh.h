#pragma once
#include "triangle.h"

struct Mesh {
    vector<Triangle> tris;
    Mtx44 matScale,
        matTranslate,
        matRotY,
        matRotX,
        matRotZ,
        matSRT;

    float thetaX,
          thetaY,
          thetaZ,
          dx,
          dy,
          dz; 

    void getMatSRT();
    void update();
};

Mesh initSquare(); 
Mesh initCube();
