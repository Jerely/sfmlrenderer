#pragma once
#include <vector>
#include "mtx44.h"
using namespace std;

struct Vec3 {
    float x, y, z;
    Vec3(float, float, float);
    Vec3();
    Vec3& operator+=(Vec3 const &);
    Vec3& operator*=(float);
    Vec3 operator+(Vec3 const &) const;
    Vec3 operator-(const Vec3&) const;
    Vec3 operator *(const float) const;
    Vec3 operator *(const Mtx44&) const;
    Vec3& operator/=(float);
    Vec3 crossProd(const Vec3&) const;
    float dotProduct(const Vec3&) const;
};

