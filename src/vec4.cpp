#include "vec4.h"

Vec4::Vec4(const Vec3& vec3, float w) :
    vec3(vec3), w(w) {};

Vec4::Vec4() :
    vec3(Vec3()), w(0) {};

Vec4 Vec4::operator *(const Mtx44& mtx44) const {
    Vec4 vec4;
    vec4.vec3.x = mtx44[0][0]*vec3.x + mtx44[1][0]*vec3.y + mtx44[2][0]*vec3.z + mtx44[3][0]*w;
    vec4.vec3.y = mtx44[0][1]*vec3.x + mtx44[1][1]*vec3.y + mtx44[2][1]*vec3.z + mtx44[3][1]*w;
    vec4.vec3.z = mtx44[0][2]*vec3.x + mtx44[1][2]*vec3.y + mtx44[2][2]*vec3.z + mtx44[3][2]*w;
    vec4.w      = mtx44[0][3]*vec3.x + mtx44[1][3]*vec3.y + mtx44[2][3]*vec3.z + mtx44[3][3]*w;
    return vec4;
}
