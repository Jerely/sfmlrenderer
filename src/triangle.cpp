#include "triangle.h"
#include "line.h"
#include "vec3.h"
#include <cmath>

Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2) :
v{v0, v1, v2} {};



Triangle::Triangle() {};


void Triangle::draw(RenderingMode mode, uint8_t* bitmap) {
    switch(mode) {
        case WIREFRAME:
            plotLine(v[0].p.x, v[0].p.y, v[1].p.x, v[1].p.y, bitmap); 
            plotLine(v[0].p.x, v[0].p.y, v[2].p.x, v[2].p.y, bitmap); 
            plotLine(v[1].p.x, v[1].p.y, v[2].p.x, v[2].p.y, bitmap); 
            break;
        case TEST:
            //...
            break;
    }
}

void Triangle::computeNorm() {
    Vec3 line1 = v[1].p - v[0].p;
    Vec3 line2 = v[2].p - v[0].p;
    norm = line1.crossProd(line2);
    //norm.z /= sqrtf(norm.dotProduct(norm));
}
