#include "triangle.h"
#include "line.h"
#include "vec4.h"
#include <cmath>
#include <algorithm>
using namespace std;

Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2) :
v{v0, v1, v2}
{};

Triangle::Triangle() {};

void Triangle::computeNorm()
{
    Vec4 line1 = v[1].p - v[0].p;
    Vec4 line2 = v[2].p - v[0].p;
    norm = line1.xyzCrossProduct(line2);
    norm.normalize();
}

void Triangle::getBoundaries(int& iMinX, int& iMinY, int& iMaxX, int& iMaxY) const
{
    float minX = min(v[0].p.x, min(v[1].p.x, v[2].p.x));
    float minY = min(v[0].p.y, min(v[1].p.y, v[2].p.y));
    float maxX = max(v[0].p.x, max(v[1].p.x, v[2].p.x));
    float maxY = max(v[0].p.y, max(v[1].p.y, v[2].p.y));
    iMinX = floatToInt(0, WIDTH-1, -1.0f, 1.0f, minX);
    iMaxX = floatToInt(0, WIDTH-1, -1.0f, 1.0f, maxX);
    iMinY = HEIGHT-1-floatToInt(0, HEIGHT-1, -1.0f, 1.0f, maxY);
    iMaxY = HEIGHT-1-floatToInt(0, HEIGHT-1, -1.0f, 1.0f, minY);
}

bool Triangle::pointIsIn(float s, float t) const
{
    //s,t and 1 - s - t are called the barycentric coordinates of the point p.
    //The point p is inside the triangle if 0 <= s <= 1 and 0 <= t <= 1 and s + t <= 1.
    return 0 <= s && s <= 1.0f && 0 <= t && t <= 1.0f && s + t <= 1.0f;
}

void Triangle::findBarycentricCoord(const Vec4& p, float& s, float& t) const
{
    s = ((v[1].p.y-v[2].p.y)*(p.x-v[2].p.x)+(v[2].p.x-v[1].p.x)*(p.y-v[2].p.y)) / ((v[1].p.y-v[2].p.y)*(v[0].p.x-v[2].p.x)+(v[2].p.x-v[1].p.x)*(v[0].p.y-v[2].p.y));
    t = ((v[2].p.y-v[0].p.y)*(p.x-v[2].p.x)+(v[0].p.x-v[2].p.x)*(p.y-v[2].p.y)) / ((v[1].p.y-v[2].p.y)*(v[0].p.x-v[2].p.x)+(v[2].p.x-v[1].p.x)*(v[0].p.y-v[2].p.y));
}
