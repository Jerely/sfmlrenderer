#include "rasterizer.h"
#include "line.h"

PhongShader phongShader;
FalseShader falseShader;

void Rasterizer::draw(const Triangle& tri)
{
    switch(mode) {
        case WIREFRAME:
            drawWireframe(tri);
            break;
        case COLORED:
            //drawColored(tri);
            colorize(tri, falseShader);
            break;
        case PHONG:
            //drawPhong(tri);
            colorize(tri, phongShader);
            break;
    }
}

Rasterizer::Rasterizer(uint8_t* bitmap) :
    mat{Vec4(.5f,.5f,.5f),
        Vec4(.5f,.5f,.5f),
        Vec4(.5f,.5f,.5f, 2.0f)},
    light{Vec4(),
          Vec4(.5f),
          Vec4(.1f, .1f, .1f),
          Vec4(),
          100.0f},
    mode(PHONG),
    perspectiveCorrect(true),
    bitmap(bitmap)
{};


void Rasterizer::computeLight(const Vec4& pos, const Vec4& normal, const Vec4& toEye, Vec4& color) const
{
    //Init outputs
    Vec4 ambient(.0f, .0f, .0f);
    Vec4 diffuse(.0f, .0f, .0f);
    Vec4 spec(.0f, .0f, .0f);

    //The vector from the surface to the light
    Vec4 lightVec = light.pos - pos;
    
    // The distance from surface to light.
    float d = lightVec.len3();

    //Range test
    if(d > light.range)
        return;
    
    // Normalize the light vector.
    lightVec /= d;

    // Ambient term.
    ambient = mat.ambient * light.ambient;

    // Add diffuse specular term, provided the surface is in

    float diffuseFactor = lightVec.dotProduct(normal);

#define max(x, y) ((x) >= (y) ? (x) : (y))
    if(diffuseFactor > .0f) {
        Vec4 v = Vec4::reflect(-lightVec, normal);
        float specFactor = pow(max(v.dotProduct(toEye), .0f), mat.spec.w);

        diffuse = mat.diffuse * light.diffuse * diffuseFactor;
        spec = mat.spec * light.spec * specFactor;
    }

    // Attenuate
    float att = 1.0f / (d*d / 25.0f);

    diffuse *= att;
    spec *= att;

    color = ambient + diffuse + spec;
}

#define v0 (tri.v[0])
#define v1 (tri.v[1])
#define v2 (tri.v[2])

void Rasterizer::drawWireframe(const Triangle& tri)
{
    plotLine(v0.p.x, v0.p.y, v1.p.x, v1.p.y, bitmap); 
    plotLine(v0.p.x, v0.p.y, v2.p.x, v2.p.y, bitmap); 
    plotLine(v1.p.x, v1.p.y, v2.p.x, v2.p.y, bitmap); 
}

void Rasterizer::drawColored(const Triangle& tri)
{
    BoundSquare bs;
    tri.getBoundingSquare(bs);
    for(int y = bs.maxY; y >= bs.minY; --y) {
        for(int x = bs.minX; x <= bs.maxX; ++x) {
            Vec4 p(intToFloat(0, WIDTH-1, -1.0f, 1.0f, x),
                   intToFloat(0, HEIGHT-1, -1.0f, 1.0f, HEIGHT-1-y));
            //s,t and 1 - s - t are called the barycentric coordinates of the point p.
            float s, t;
            tri.findBarycentricCoord(p, s, t);
            if(tri.pointIsIn(s, t)) {
                Vec4 vecColor;
                falseShading(tri, s, t, vecColor);
                Color color = vecColor.toColor();
                setPixel(bitmap, x, y, color);
            }
        }
    }
}

void Rasterizer::drawPhong(const Triangle& tri)
{
    BoundSquare bs;
    tri.getBoundingSquare(bs);
    for(int y = bs.maxY; y >= bs.minY; --y) {
        for(int x = bs.minX; x <= bs.maxX; ++x) {
            Vec4 p(intToFloat(0, WIDTH-1, -1.0f, 1.0f, x),
                   intToFloat(0, HEIGHT-1, -1.0f, 1.0f, HEIGHT-1-y));
            //s,t and 1 - s - t are called the barycentric coordinates of the point p.
            float s, t;
            tri.findBarycentricCoord(p, s, t);
            if(tri.pointIsIn(s, t)) {
                Vec4 vecColor;
                phongShading(tri, s, t, vecColor);
                Color color = vecColor.toColor();
                setPixel(bitmap, x, y, color);
            }
        }
    }
}

void Rasterizer::colorize(const Triangle& tri, Shader& shader)
{
    BoundSquare bs;
    tri.getBoundingSquare(bs);
    for(int y = bs.maxY; y >= bs.minY; --y) {
        for(int x = bs.minX; x <= bs.maxX; ++x) {
            Vec4 p(intToFloat(0, WIDTH-1, -1.0f, 1.0f, x),
                   intToFloat(0, HEIGHT-1, -1.0f, 1.0f, HEIGHT-1-y));
            //s,t and 1 - s - t are called the barycentric coordinates of the point p.
            float s, t;
            tri.findBarycentricCoord(p, s, t);
            if(tri.pointIsIn(s, t)) {
                Vec4 vecColor;
                shader(*this, tri, s, t, vecColor);
                Color color = vecColor.toColor();
                setPixel(bitmap, x, y, color);
            }
        }
    }
}

void Rasterizer::phongShading(const Triangle& tri, float s, float t, Vec4& vecColor) const
{
    Vec4 pos;
    tri.findPointInWorld(s, t, pos);
    computeLight(pos, tri.norm, (eyePos-pos).normalize(), vecColor);
}

void Rasterizer::falseShading(const Triangle& tri, float s, float t, Vec4& vecColor) const
{
    tri.determineColor(s, t, vecColor);
}

void PhongShader::operator()(const Rasterizer& r, const Triangle& tri, float s, float t, Vec4& vecColor)
{
    r.phongShading(tri, s, t, vecColor);
}

void FalseShader::operator()(const Rasterizer& r, const Triangle& tri, float s, float t, Vec4& vecColor)
{
    r.falseShading(tri, s, t, vecColor);
}
