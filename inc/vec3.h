#pragma once
#include <vector>
using namespace std;

struct Vec3 {
    float x, y, z;
    Vec3(float, float, float);
    Vec3();
    Vec3& operator+=(Vec3 const &);
    Vec3& operator*=(float);
    Vec3 operator+(Vec3 const &) const;
    Vec3 operator *(const float) const;
};

struct Mtx44 {
    float m[4][4];
};

