#include "rasterizer.h"
#include "line.h"

void Rasterizer::draw(const Triangle& tri)
{
    const Vertex& v0 = tri.v[0];
    const Vertex& v1 = tri.v[1];
    const Vertex& v2 = tri.v[2];
    switch(mode) {
        case WIREFRAME:
            plotLine(v0.p.x, v0.p.y, v1.p.x, v1.p.y, bitmap); 
            plotLine(v0.p.x, v0.p.y, v2.p.x, v2.p.y, bitmap); 
            plotLine(v1.p.x, v1.p.y, v2.p.x, v2.p.y, bitmap); 
            break;
        case COLORED:
            int iMinX, iMinY, iMaxX, iMaxY;
            tri.getBoundaries(iMinX, iMinY, iMaxX, iMaxY);
            for(int y = iMaxY; y >= iMinY; --y) {
                for(int x = iMinX; x <= iMaxX; ++x) {
                    Vec4 p(intToFloat(0, WIDTH-1, -1.0f, 1.0f, x),
                           intToFloat(0, HEIGHT-1, -1.0f, 1.0f, HEIGHT-1-y));
                    //s,t and 1 - s - t are called the barycentric coordinates of the point p.
                    float s, t;
                    tri.findBarycentricCoord(p, s, t);
                    if(tri.pointIsIn(s, t)) {
                        Color color;
                        determineColor(tri, s, t, color);
                        setPixel(bitmap, x, y, color);
                    }
                }
            }
            break;
    }
}

Rasterizer::Rasterizer(uint8_t* bitmap) :
    mode(COLORED),
    perspectiveCorrect(true),
    bitmap(bitmap)
{};

void Rasterizer::determineColor(const Triangle& tri, float s, float t, Color& color)
{
    const Vertex& v0 = tri.v[0];
    const Vertex& v1 = tri.v[1];
    const Vertex& v2 = tri.v[2];
    //получаем третью координату
    float u = 1 - s - t;

    //преобразуем цвета из формата int8*3 в формат float*3
    Vec4 c0 = v0.color.toVec3();
    Vec4 c1 = v1.color.toVec3();
    Vec4 c2 = v2.color.toVec3();
    
    //делим цвета на координату z
    if(perspectiveCorrect) {
        c0 *= v0.p.w;
        c1 *= v1.p.w;
        c2 *= v2.p.w;
    }

    //интерполируем цвета
    Vec4 vecColor = c0 * s + c1 * t + c2 * u;

    //Для корректной с точки зрения перспективы интерполяци мы умножаем
    //результат на z, глубину точки на трехмерном треугольнике, который
    //пиксель перекрывает.
    if(perspectiveCorrect) {
        float z = 1 / (s * v0.p.w + t * v1.p.w + u * v2.p.w);
        vecColor *= z;
    }

    //Преобразуем обратно в формат int8*3
    color.r = (uint8_t) floatToInt(0, 255, .0f, 1.0f, vecColor.x);
    color.g = (uint8_t) floatToInt(0, 255, .0f, 1.0f, vecColor.y);
    color.b = (uint8_t) floatToInt(0, 255, .0f, 1.0f, vecColor.z);
    color.a = 255;
}
