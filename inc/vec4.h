#pragma once
#include <vector>
#include "mtx44.h"
#include "vec3.h"
using namespace std;

struct Vec4 {
    Vec3& vec3;
    float w;
    Vec4();
    Vec4(const Vec3&, float);
    Vec4 operator *(const Mtx44&) const;
};
