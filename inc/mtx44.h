#pragma once

struct Mtx44 {
    float m[4][4];
    Mtx44 operator *(const Mtx44&);
    static Mtx44 rotateX(float angle);
    static Mtx44 rotateY(float angle);
    static Mtx44 rotateZ(float angle);
    static Mtx44 translate(float, float, float);
    static Mtx44 scale(float q);
    static Mtx44 project(float, float, float, float);
    Mtx44();
};


