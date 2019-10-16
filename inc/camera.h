#pragma once
#include "vec4.h"
#include "mtx44.h"

struct Camera {
    Vec4 pos, target, up;
    float angleH, angleV;
    uint32_t mousePosX;
    uint32_t mousePosY;
    bool onUpperEdge, onLowerEdge, onLeftEdge, onRightEdge;
    static const uint32_t MARGIN;

    Camera();
    Mtx44 initCameraTransform();
    void onMouse(uint32_t, uint32_t);
    void onRender();
    void update();
};
