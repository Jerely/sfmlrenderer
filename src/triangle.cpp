#include "triangle.h"
#include "line.h"
#include "vec3.h"
#include <cmath>

Triangle::Triangle() :
    p{Vec3(), Vec3(), Vec3()} {};

Triangle::Triangle(Vec3 const &p0, Vec3 const &p1, Vec3 const &p2) :
    p{p0, p1, p2}
{
};

void drawTriangle(Triangle& tri, uint8_t* bitmap) {
   plotLine(tri.p[0].x, tri.p[0].y, tri.p[1].x, tri.p[1].y, bitmap); 
   plotLine(tri.p[0].x, tri.p[0].y, tri.p[2].x, tri.p[2].y, bitmap); 
   plotLine(tri.p[1].x, tri.p[1].y, tri.p[2].x, tri.p[2].y, bitmap); 
}

void Triangle::computeNorm() {
    Vec3 line1 = p[1] - p[0];
    Vec3 line2 = p[2] - p[0];
    norm = line1.crossProd(line2);
    //norm.z /= sqrtf(norm.dotProduct(norm));
}
