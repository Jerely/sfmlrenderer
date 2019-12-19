#include "rasterizer.h"
#include "line.h"



void Rasterizer::draw(Triangle& tri, bool isAlwaysWireframe)
{
    static Shader phongShader =
        [] (const Rasterizer& r, const Triangle& tri, float s, float t, Vec4& vecColor)
        {
            r.phongShading(tri, s, t, vecColor);
        };
    static Shader gouraudShader =
        [] (const Rasterizer& r, const Triangle& tri, float s, float t, Vec4& vecColor)
        {
            r.gouraudShading(tri, s, t, vecColor);
        };
	static Shader flatShader =
		[](const Rasterizer& r, const Triangle& tri, float s, float t, Vec4& vecColor)
	{
		r.flatShading(tri, vecColor);
	};
		
	if (isAlwaysWireframe) {
		drawWireframe(tri);
		return;
	}
    switch(mode) {
        case WIREFRAME:
            drawWireframe(tri);
            break;
        case PHONG:
            colorize(tri, phongShader);
            break;
		case GOURAUD:
			computeVertexColor(tri);
			colorize(tri, gouraudShader);
			break;
		case FLAT:
			computeVertexColor(tri);
			colorize(tri, flatShader);
    }
}

void Rasterizer::updateLights() {
	float attBase = 20.f;
	float difBase = 2.f;
	float att = attBase * pow(10, exp);
	float diff = difBase * pow(10, exp);
	light0.ambient = Vec4(0.0005f, 0.0005f, 0.0005f) * pow(10.f, brightness);
	light0.diffuse = Vec4(diff)* pow(10.f, brightness);
	light0.spec = Vec4(diff/10.f, diff/10.f, diff/10.f) * pow(10.f, brightness);
	light0.pos = Vec4(-0.8f, -0.7f, 4.9f);
	light0.dir = Vec4(.19f, .34f, .92f);
	light0.range = 100.f;
	light0.spot = 8.0f;
	light0.att = Vec4(att, att, att);

	light1.ambient = Vec4(0.0005f, 0.0005f, 0.0005f) * pow(10.f, brightness);
	light1.diffuse = Vec4(.0f, diff) * pow(10.f, brightness);
	light1.spec = Vec4(diff/10.f, diff/10.f, diff/10.f) * pow(10.f, brightness);
	light1.pos = Vec4(.6f, -0.3f, 4.6f);
	light1.dir = Vec4(-0.21f, 0.33f, 0.92f);
	light1.range = 100.f;
	light1.spot = 8.0f;
	light1.att = Vec4(att, att, att);


	light2.ambient = Vec4(0.0005f, 0.0005f, 0.0005f) * pow(10.f, brightness);
	light2.diffuse = Vec4(.0f, .0f, diff) * pow(10.f, brightness);
	light2.spec = Vec4(diff/10.f, diff/10.f, diff/10.f) * pow(10.f, brightness);
	light2.pos = Vec4(0.f, 1.5f, 5.2f);
	light2.dir = Vec4(0.0173f, -0.96f, 0.28f);
	light2.range = 100.f;
	light2.spot = 8.0f;
	light2.att = Vec4(att, att, att);
}

Rasterizer::Rasterizer(uint8_t* bitmap) :
	exp(5.f),
	brightness(0),
    mat{Vec4(.5f,.5f,.5f),
        Vec4(.5f,.5f,.5f),
        Vec4(.5f,.5f,.5f, 2.0f)},
    mode(PHONG),
    perspectiveCorrect(true),
    bitmap(bitmap)
{
	updateLights();
};

void Rasterizer::pixelShader(const Vec4& pos, const Vec4& normal, const Vec4& toEye, Vec4& color) const
{
	Vec4 ambient, diffuse, spec;
	{
		Vec4 a, d, s;
		computeLight(light0, pos, normal, toEye, a, d, s);
		ambient += a;
		diffuse += d;
		spec += s;
	}
	{
		Vec4 a, d, s;
		computeLight(light1, pos, normal, toEye, a, d, s);
		ambient += a;
		diffuse += d;
		spec += s;
	}
	{
		Vec4 a, d, s;
		computeLight(light2, pos, normal, toEye, a, d, s);
		ambient += a;
		diffuse += d;
		spec += s;
	}
    color = ambient + diffuse + spec;
}

 void Rasterizer::computeLight(const Light& light, const Vec4& pos, const Vec4& normal, const Vec4& toEye, Vec4& ambient, Vec4& diffuse, Vec4& spec) const {

    //Init outputs
    ambient = Vec4(.0f, .0f, .0f);
    diffuse = Vec4(.0f, .0f, .0f);
    spec = Vec4(.0f, .0f, .0f);

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

	float spot = pow(max((-lightVec).dotProduct(light.dir), 0), light.spot);

    // Attenuate
	float att = spot / light.att.dotProduct(Vec4(1.f, d, d * d));

	ambient *= spot;
    diffuse *= att;
    spec *= att;
	 // // Scale by spotlight factor and attenuate.
	 // float spot = pow(max(dot(-lightVec, L.Direction), 0.0f), L.Spot);

	 // // Scale by spotlight factor and attenuate.
	 // float att = spot / dot(L.Att, float3(1.0f, d,
	 // 	d * d));
	 // ambient *= spot;
	 // diffuse *= att;
	 // spec *= att;

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

void Rasterizer::phongShading(const Triangle& tri, float s, float t, Vec4& vecColor) const
{
    Vec4 pos;
    tri.findPointInWorld(s, t, pos);
    pixelShader(pos, tri.norm, (eyePos-pos).normalize(), vecColor);
}



void Rasterizer::gouraudShading(const Triangle& tri, float s, float t, Vec4& vecColor) const
{
    tri.interpolateColor(s, t, vecColor);
}

void Rasterizer::flatShading(const Triangle& tri, Vec4& vecColor) const
{
	for (const auto& vtx : tri.v) {
		vecColor += vtx.color.toVec3();
	}
	vecColor *= 0.33f;
}

void Rasterizer::computeVertexColor(Triangle& tri) const
{
	for (auto& vtx : tri.v) {
		Vec4 color;
		pixelShader(vtx.wPos, tri.norm, (eyePos - vtx.wPos).normalize(), color);
		vtx.color = color.toColor();
	}

}

void Rasterizer::colorize(const Triangle& tri, Shader shader)
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
