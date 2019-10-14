#pragma once

struct Mtx44 {
    float m[4][4];
    Mtx44 operator *(const Mtx44&);
    Mtx44();
};

Mtx44 MatrixQuickInverse(Mtx44 &m);
