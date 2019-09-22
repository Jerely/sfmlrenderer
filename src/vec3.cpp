#include "vec3.h"


Vec3::Vec3(float x, float y, float z) :
    x(x), y(y), z(z) {};

Vec3::Vec3() :
    x(.0f), y(.0f), z(.0f) {};

Vec3& Vec3::operator+=(Vec3 const & shift) {
    this->x += shift.x;
    this->y += shift.y;
    this->z += shift.z;
    return *this;
}

Vec3& Vec3::operator*=(float scale) {
    this->x *= scale;
    this->y *= scale;
    this->z *= scale;
    return *this;
}


Vec3 Vec3::operator+(Vec3 const & shift) const {
    Vec3 v;
    v.x = this->x + shift.x;
    v.y = this->y + shift.y;
    v.z = this->z + shift.z;
    return v;
}

Vec3 Vec3::operator *(const float scale) const {
    Vec3 v;
    v.x = this->x * scale;
    v.y = this->y * scale;
    v.z = this->z * scale;
    return v;
}


Vec3 Vec3::operator *(const Mtx44& m) const {
    Vec3 v;
    float w;
    v.x = x * m.m[0][0] + y * m.m[1][0] + z * m.m[2][0] + m.m[3][0];
    v.y = x * m.m[0][1] + y * m.m[1][1] + z * m.m[2][1] + m.m[3][1];
    v.z = x * m.m[0][2] + y * m.m[1][2] + z * m.m[2][2] + m.m[3][2];
    w   = x * m.m[0][3] + y * m.m[1][3] + z * m.m[2][3] + m.m[3][3];
    if (w != 0.0f) {
        v.x /= w;
        v.y /= w;
        v.z /= w;
    }
    return v;
}


Vec3 Vec3::crossProd(const Vec3& in) const {
    Vec3 out;
    out.x = y * in.z - z * in.y;
    out.y = z * in.x - x * in.z;
    out.z = x * in.y - y * in.x;
    return out;
}

Vec3 Vec3::operator-(const Vec3& in) const {
    Vec3 out;
    out.x = x - in.x;
    out.y = y - in.y;
    out.z = z - in.z;
    return out;
}



float Vec3::dotProduct(const Vec3& in) const {
    return x * in.x + y * in.y + z * in.z;
}


Vec3& Vec3::operator/=(float q) {
    x /= q;
    y /= q;
    z /= q;
    return *this;
}
