#include "camera.h"

const uint32_t Camera::MARGIN = 10; 

Mtx44 Camera::initCameraTransform()
{
    /*
    Mtx44 m;
    Vec4 v = n.crossProduct(u);
    m[0][0] = up.x; m[0][1] = up.y; m[0][2] = up.z; m[0][3] = 0.0f;
    m[1][0] = v.x; m[1][1] = v.y; m[1][2] = v.z; m[1][3] = 0.0f;
    m[2][0] = target.x; m[2][1] = target.y; m[2][2] = target.z; m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
    return m;
    */
}

Camera::Camera()
    /*
      :
    target(.0f, .0f, 1.0f),
    up(.0f, 1.0f, .0f),
    angleH(.0f),
    angleV(.0f),
    onUpperEdge(false),
    onLowerEdge(false),
    onLeftEdge(false),
    onRightEdge(false),
    mousePosX(WIDTH/2),
    mousePosY(HEIGHT/2) */
{};

void Camera::onMouse(uint32_t x, uint32_t y) {
    /*const int dx = x - mousePosX;
    const int dy = y - mousePosY;
    mousePosX = x;
    mousePosY = y;
    angleH += (float) dx / 20.0f;
    angleV += (float) dy / 20.0f;

    if(dx == 0) {
        (if x <= MARGIN) {
            onLeftEdge = true;
        }
        else if (x >= WIDTH - MARGIN) {
            onRightEdge = true;
        }
    }
    else {
        onLeftEdge = false;
        onLeftEdge = false;
    }

    if(dy == 0) {
        if (y <= MARGIN) {
            onUpperEdge = true;
        }
        else if (y >= HEIGHT - MARGIN) {
            onLowerEdge = true;
        }
    }
    else {
        onUpperEdge = false;
        onLowerEdge = false;
    }

    update();*/
}

void Camera::onRender()
{
    /*bool shouldUpdate = false;
    if(onLeftEdge) {
        angleH -= 0.1f;
        shouldUpdate = true;
    }
    else if(onRightEdge) {
        angleH += 0.1f;
        shouldUpdate = true;
    }

    if(onUpperEdge) {
        if(angleV > -90.0f) {
            angleV -= 0.1f;
            shouldUpdate = true;
        }
    }
    else if(onLowerEdge) {
        if(angleV < 90.0f) {
            angleV += 0.1f;
            shouldUpdate = true;
        }
    }

    if(shouldUpdate) {
        update();
        }*/
}

void Camera::update()
{
    /*const Vec4 vAxis(0.0f, 1.0f, 0.0f);

    Vec4 view(1.0f, 0.0f, 0.0f);
    view.rotate(angleH, vAxis);
    view.normalize();

    Vec4 hAxis = vAxis.crossProduct(view);
    hAxis.normalize();
    view.rotate(angleV, hAxis);
    view.normalize();

    target = view;
    target.normalize();

    up = target.cross(hAxis);
    up.normalize();*/
}


  
