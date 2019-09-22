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

void Triangle::draw(RenderingMode mode, uint8_t* bitmap) {
    switch(mode) {
        case WIREFRAME:
            plotLine(p[0].x, p[0].y, p[1].x, p[1].y, bitmap); 
            plotLine(p[0].x, p[0].y, p[2].x, p[2].y, bitmap); 
            plotLine(p[1].x, p[1].y, p[2].x, p[2].y, bitmap); 
            break;
        case TEST:
            //...
            break;
    }
}

void Triangle::computeNorm() {
    Vec3 line1 = p[1] - p[0];
    Vec3 line2 = p[2] - p[0];
    norm = line1.crossProd(line2);
    //norm.z /= sqrtf(norm.dotProduct(norm));
}
