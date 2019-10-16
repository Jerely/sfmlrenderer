#pragma once

struct Mtx44 {
    float m[4][4];
    Mtx44 operator *(const Mtx44&);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void translate(float, float, float);
    void scale(float q);
    void project(float, float, float, float);
    Mtx44();
};

Mtx44 MatrixQuickInverse(Mtx44 &m);


