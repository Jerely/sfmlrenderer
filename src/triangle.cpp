#include "triangle.h"
#include "line.h"
#include "vec4.h"
#include <cmath>
#include <algorithm>
using namespace std;

Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
};

Triangle::Triangle() {};

void Triangle::computeNorm()
{
    Vec4 line1 = v[1].wPos - v[0].wPos;
    Vec4 line2 = v[2].wPos - v[0].wPos;
    norm = line1.xyzCrossProduct(line2);
    norm.normalize();
}

void Triangle::getBoundingSquare(BoundSquare& bs) const
{
    float minX = min(v[0].p.x, min(v[1].p.x, v[2].p.x));
    float minY = min(v[0].p.y, min(v[1].p.y, v[2].p.y));
    float maxX = max(v[0].p.x, max(v[1].p.x, v[2].p.x));
    float maxY = max(v[0].p.y, max(v[1].p.y, v[2].p.y));
    bs.minX = floatToInt(0, WIDTH-1, -1.0f, 1.0f, minX);
    bs.maxX = floatToInt(0, WIDTH-1, -1.0f, 1.0f, maxX);
    bs.minY = HEIGHT-1-floatToInt(0, HEIGHT-1, -1.0f, 1.0f, maxY);
    bs.maxY = HEIGHT-1-floatToInt(0, HEIGHT-1, -1.0f, 1.0f, minY);
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

void Triangle::determineColor(float s, float t, Vec4& vecColor) const
{
#define v0 (v[0])
#define v1 (v[1])
#define v2 (v[2])

    //получаем третью координату
    float u = 1 - s - t;

    //преобразуем цвета из формата int8*3 в формат float*3
    Vec4 c0 = v0.color.toVec3();
    Vec4 c1 = v1.color.toVec3();
    Vec4 c2 = v2.color.toVec3();
    
    //делим цвета на координату z
    //if(perspectiveCorrect) {
        c0 *= v0.p.w;
        c1 *= v1.p.w;
        c2 *= v2.p.w;

    //интерполируем цвета
    vecColor = c0 * s + c1 * t + c2 * u;

    //Для корректной с точки зрения перспективы интерполяци мы умножаем
    //результат на z, глубину точки на трехмерном треугольнике, который
    //пиксель перекрывает.
    //if(perspectiveCorrect) {
        float z = 1 / (s * v0.p.w + t * v1.p.w + u * v2.p.w);
        vecColor *= z;
}

void Triangle::findPointInWorld(float s, float t, Vec4& pos) const 
{
    float u = 1 - s - t;
    Vec4 wPos0 = v0.wPos * v0.p.w;
    Vec4 wPos1 = v1.wPos * v1.p.w;
    Vec4 wPos2 = v2.wPos * v2.p.w;

    pos = wPos0 * s + wPos1 * t + wPos2 * u;
    float z = 1 / (s * v0.p.w + t * v1.p.w + u * v2.p.w);
    pos *= z;
}
