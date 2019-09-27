#include "triangle.h"
#include "line.h"
#include "vec3.h"
#include <cmath>
#include <algorithm>

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
        case COLORED:
            int iMinX, iMinY, iMaxX, iMaxY;
            intBoundaries(iMinX, iMinY, iMaxX, iMaxY);
            for(int y = iMaxY; y >= iMinY; --y) {
                for(int x = iMinX; x <= iMaxX; ++x) {
                    Vec3 p(intToFloat(0, WIDTH-1, -1.0f, 1.0f, x),
                           intToFloat(0, HEIGHT-1, -1.0f, 1.0f, HEIGHT-1-y), .0f);
                    //s,t and 1 - s - t are called the barycentric coordinates of the point p.
                    float s, t;
                    findBarycentricCoord(p, s, t);
                    if(pointIsIn(s, t)) {
                        Color color;
                        determineColor(s, t, color);
                        setPixel(bitmap, x, y, color);
                    }
                }
            }
            //displayBitmap(*pWindow, bitmap);
            break;
    }
}

void Triangle::computeNorm() {
    Vec3 line1 = v[1].p - v[0].p;
    Vec3 line2 = v[2].p - v[0].p;
    norm = line1.crossProd(line2);
    //norm.z /= sqrtf(norm.dotProduct(norm));
}



void Triangle::getBoundaries(float& minX, float& minY, float& maxX, float& maxY) {
    minX = std::min(v[0].p.x, std::min(v[1].p.x, v[2].p.x));
    minY = std::min(v[0].p.y, std::min(v[1].p.y, v[2].p.y));
    maxX = std::max(v[0].p.x, std::max(v[1].p.x, v[2].p.x));
    maxY = std::max(v[0].p.y, std::max(v[1].p.y, v[2].p.y));
    /*
    minX = v[0].p.x;
    for(int i = 1; i < 3; ++i) {
        if(v[i].p.x < minX) {
            minX = v[i].p.x;
        }
    }
    minY = v[0].p.y;
    for(int i = 1; i < 3; ++i) {
        if(v[i].p.y < minY) {
            minY = v[i].p.y;
        }
    }
    maxX = v[0].p.x;
    for(int i = 1; i < 3; ++i) {
        if(v[i].p.x > maxX) {
            maxX = v[i].p.x;
        }
    }
    maxY = v[0].p.y;
    for(int i = 1; i < 3; ++i) {
        if(v[i].p.y > maxY) {
            maxY = v[i].p.y;
        }
    }
    */
}


void Triangle::intBoundaries(int& iMinX, int& iMinY, int& iMaxX, int& iMaxY) {
    float minX, minY, maxX, maxY;
    getBoundaries(minX, minY, maxX, maxY);
    iMinX = floatToInt(0, WIDTH-1, -1.0f, 1.0f, minX);
    iMaxX = floatToInt(0, WIDTH-1, -1.0f, 1.0f, maxX);
    iMinY = HEIGHT-1-floatToInt(0, HEIGHT-1, -1.0f, 1.0f, maxY);
    iMaxY = HEIGHT-1-floatToInt(0, HEIGHT-1, -1.0f, 1.0f, minY);
}


void Triangle::determineColor(float s, float t, Color& color) {
    Vec3 vecColor = v[0].color.toVec3() * s + v[1].color.toVec3() * t + v[2].color.toVec3() * (1-s-t);
    color.r = (uint8_t) floatToInt(0, 255, .0f, 1.0f, vecColor.x);
    color.g = (uint8_t) floatToInt(0, 255, .0f, 1.0f, vecColor.y);
    color.b = (uint8_t) floatToInt(0, 255, .0f, 1.0f, vecColor.z);
    color.a = 255;
}

bool Triangle::pointIsIn(float s, float t) {
    //s,t and 1 - s - t are called the barycentric coordinates of the point p.
    //The point p is inside the triangle if 0 <= s <= 1 and 0 <= t <= 1 and s + t <= 1.
    return 0 <= s && s <= 1.0f && 0 <= t && t <= 1.0f && s + t <= 1.0f;
}

void Triangle::findBarycentricCoord(const Vec3& p, float& s, float& t) {
    /*
    s = ((yv2-yv3)*(px-xv3)+(xv3-xv2)*(py-yv3)) /
        ((yv2-yv3)*(xv1-xv3)+(xv3-xv2)*(yv1-yv3));
    t = ((yv3-yv1)*(px-xv3)+(xv1-xv3)*(py-yv3)) /
        ((yv2-yv3)*(xv1-xv3)+(xv3-xv2)*(yv1-yv3));
        */
    s = ((v[1].p.y-v[2].p.y)*(p.x-v[2].p.x)+(v[2].p.x-v[1].p.x)*(p.y-v[2].p.y)) / ((v[1].p.y-v[2].p.y)*(v[0].p.x-v[2].p.x)+(v[2].p.x-v[1].p.x)*(v[0].p.y-v[2].p.y));
    t = ((v[2].p.y-v[0].p.y)*(p.x-v[2].p.x)+(v[0].p.x-v[2].p.x)*(p.y-v[2].p.y)) / ((v[1].p.y-v[2].p.y)*(v[0].p.x-v[2].p.x)+(v[2].p.x-v[1].p.x)*(v[0].p.y-v[2].p.y));
}


