#include "vec4.h"
#include <cmath>


Vec4::Vec4(float x, float y, float z, float w) :
    x(x), y(y), z(z), w(w) {};

Vec4::Vec4(float x, float y) :
    x(x), y(y), z(.0f), w(1.0f) {};

Vec4::Vec4(float x, float y, float z) :
    x(x), y(y), z(z), w(1.0f) {};

Vec4::Vec4() :
    x(.0f), y(.0f), z(.0f), w(1.0f) {};

Vec4& Vec4::operator+=(Vec4 const & shift) {
    this->x += shift.x;
    this->y += shift.y;
    this->z += shift.z;
    this->w += shift.w;
    return *this;
}

Vec4& Vec4::operator*=(float scale) {
    this->x *= scale;
    this->y *= scale;
    this->z *= scale;
    this->w *= scale;
    return *this;
}


Vec4 Vec4::operator+(Vec4 const & shift) const {
    Vec4 v;
    v.x = this->x + shift.x;
    v.y = this->y + shift.y;
    v.z = this->z + shift.z;
    v.w = this->w + shift.w;
    return v;
}

Vec4 Vec4::operator *(const float scale) const {
    Vec4 v;
    v.x = this->x * scale;
    v.y = this->y * scale;
    v.z = this->z * scale;
    v.w = this->w * scale;
    return v;
}


Vec4 Vec4::operator *(const Mtx44& m) const {
    Vec4 v;
    v.x = x * m.m[0][0] + y * m.m[1][0] + z * m.m[2][0] + w * m.m[3][0];
    v.y = x * m.m[0][1] + y * m.m[1][1] + z * m.m[2][1] + w * m.m[3][1];
    v.z = x * m.m[0][2] + y * m.m[1][2] + z * m.m[2][2] + w * m.m[3][2];
    v.w = x * m.m[0][3] + y * m.m[1][3] + z * m.m[2][3] + w * m.m[3][3];
    return v;
}


Vec4 Vec4::xyzCrossProduct(const Vec4& in) const {
    Vec4 out;
    out.x = y * in.z - z * in.y;
    out.y = z * in.x - x * in.z;
    out.z = x * in.y - y * in.x;
    out.w = 0.0f;
    return out;
}

Vec4 Vec4::operator-(const Vec4& in) const {
    Vec4 out;
    out.x = x - in.x;
    out.y = y - in.y;
    out.z = z - in.z;
    out.w = w - in.w;
    return out;

}

float Vec4::dotProduct(const Vec4& in) const {
    return x * in.x + y * in.y + z * in.z + w * in.w;
}


Vec4& Vec4::operator/=(float q) {
    x /= q;
    y /= q;
    z /= q;
    w /= q;
    return *this;
}

void Vec4::perspDiv() {
    if(w != 0) {
        x /= w;
        y /= w;
        z /= w;
    }
}

void Vec4::normalize() {
    float len = sqrtf(x*x + y*y + z*z + w*w);
    x /= len;
    y /= len;
    z /= len;
    w /= len;
}
