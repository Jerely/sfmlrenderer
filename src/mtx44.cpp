#include "mtx44.h"
#include <cmath>

Mtx44::Mtx44() :
    m{0} {};

Mtx44 Mtx44::operator *(const Mtx44& mat) {
    Mtx44 result;
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            result.m[i][j] = 0;
            for(int k = 0; k < 4; ++k) {
                result.m[i][j] += m[i][k] * mat.m[k][j];
            }
        }
    }
    return result;
}

Mtx44 Mtx44::rotateY(float angle) {
    Mtx44 out;
    out.m[0][0] = cosf(angle);
    out.m[0][2] = -sinf(angle);
    out.m[1][1] = 1.0f;
    out.m[2][0] = sinf(angle);
    out.m[2][2] = cosf(angle);
    out.m[3][3] = 1.0f;
    return out;
}

Mtx44 Mtx44::rotateX(float angle) {
    Mtx44 out;
    out.m[0][0] = 1.0f;
    out.m[1][1] = cosf(angle);
    out.m[1][2] = sinf(angle);
    out.m[2][1] = -sinf(angle);
    out.m[2][2] = cosf(angle);
    out.m[3][3] = 1.0f;
    return out;
}

Mtx44 Mtx44::rotateZ(float angle) {
    Mtx44 out;
    out.m[0][0] = cosf(angle);
    out.m[0][1] = sinf(angle);
    out.m[1][0] = -sinf(angle);
    out.m[1][1] = cosf(angle);
    out.m[2][2] = 1.0f;
    out.m[3][3] = 1.0f;
    return out;
}


Mtx44 Mtx44::project(float ar,
                     float near,
                     float far,
                     float fov)
{
    Mtx44 out;
    float range = far - near;
    float tanHalfFov = tanf(fov * .5f / 180.0f * 3.14159f);

    out.m[0][0] = 1.0f / (tanHalfFov * ar);
    out.m[1][1] = 1.0f / tanHalfFov;
    out.m[2][2] = far / range;
    out.m[2][3] = 1.0f;
    out.m[3][2] = - far * near / range;
    return out;
}

Mtx44 Mtx44::translate(float x, float y, float z)
{
    Mtx44 out;
    out.m[0][0] = 1.0f;
    out.m[1][1] = 1.0f;
    out.m[2][2] = 1.0f;
    out.m[3][3] = 1.0f;
    out.m[3][0] = x;
    out.m[3][1] = y;
    out.m[3][2] = z;
    return out;
}

Mtx44 Mtx44::scale(float q) {
    Mtx44 out;
    out.m[0][0] = q;
    out.m[1][1] = q;
    out.m[2][2] = q;
    out.m[3][3] = 1.0f;
    return out;
}
