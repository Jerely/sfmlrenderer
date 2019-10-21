#pragma once
#include <vector>
#include "mtx44.h"

struct Color;

struct Vec4 {
    float x, y, z, w;
    Vec4(float, float, float, float);
    Vec4(float, float, float);
    Vec4(float, float);
    Vec4(float);
    Vec4();
    Vec4& operator+=(Vec4 const &);
    Vec4& operator-=(Vec4 const &);
    Vec4& operator*=(float);
    Vec4 operator+(Vec4 const &) const;
    Vec4 operator-(const Vec4&) const;
    Vec4 operator-() const;
    Vec4 operator *(const float) const;
    Vec4 operator *(const Mtx44&) const;
    Vec4 operator *(const Vec4&) const; // component-wise
    Vec4& operator/=(float);
    static Vec4 reflect(const Vec4&, const Vec4&);
    Color toColor() const;
    
    Vec4 xyzCrossProduct(const Vec4&) const;
    float dotProduct(const Vec4&) const;
    void perspDiv();
    Vec4& normalize();
    float len3() const;
};

