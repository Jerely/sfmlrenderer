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
