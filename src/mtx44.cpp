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

Mtx44 MatrixQuickInverse(Mtx44 &m) // Only for Rotation/Translation Matrices
{
    Mtx44 matrix;
    matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
    matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
    matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
    matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
    matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
    matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
    matrix.m[3][3] = 1.0f;
    return matrix;
}

void Mtx44::rotateY(float angle) {
    m[0][0] = cosf(angle);
    m[0][2] = -sinf(angle);
    m[1][1] = 1.0f;
    m[2][0] = sinf(angle);
    m[2][2] = cosf(angle);
    m[3][3] = 1.0f;
}

void Mtx44::rotateX(float angle) {
    m[0][0] = 1.0f;
    m[1][1] = cosf(angle);
    m[1][2] = sinf(angle);
    m[2][1] = -sinf(angle);
    m[2][2] = cosf(angle);
    m[3][3] = 1.0f;
}

void Mtx44::rotateZ(float angle) {
    m[0][0] = cosf(angle);
    m[0][1] = sinf(angle);
    m[1][0] = -sinf(angle);
    m[1][1] = cosf(angle);
    m[2][2] = 1.0f;
    m[3][3] = 1.0f;
}


void Mtx44::project(float ar,
                     float near,
                     float far,
                     float fov)
{
    float range = near - far;
    float tanHalfFov = tanf(fov * .5f / 180.0f * 3.14159f);

    m[0][0] = 1.0f / (tanHalfFov * ar);
    m[1][1] = 1.0f / tanHalfFov;
    m[2][2] = (-near - far) / range;
    m[2][3] = 2.0f * far * near / range;
    m[3][2] = 1.0f;
}

void Mtx44::translate(float x, float y, float z)
{
    m[0][0] = 1.0f;
    m[1][1] = 1.0f;
    m[2][2] = 1.0f;
    m[3][3] = 1.0f;
    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
}

void Mtx44::scale(float q) {
    m[0][0] = q;
    m[1][1] = q;
    m[2][2] = q;
    m[3][3] = 1.0f;
}
