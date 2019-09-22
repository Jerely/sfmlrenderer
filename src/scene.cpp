#include "scene.h"


Scene::Scene() :
thetaX(0), thetaY(0), thetaZ(0), dx(0), dy(0), dz(0)
{
    initCube();
    project();
};

void MultiplyMatrixVector2(Vec3 &i, Vec3 &o, Mtx44 &m) {
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
}

void MultiplyMatrixVector(Vec3 &i, Vec3 &o, Mtx44 &m) {
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

    if(w == 0.0f)
        w = 0.001f;
    o.x /= w; o.y /= w; o.z /= w;
}

void fillPixels(uint8_t* bitmap, Color color) {
    for(uint32_t y = 0; y < HEIGHT; y++) {
        for(uint32_t x = 0; x < WIDTH; x++) {
            setPixel(bitmap, x, y, color);
        }
    }
}

void Scene::rotateY(float angle) {
    matRotY.m[0][0] = cosf(angle);
    matRotY.m[0][2] = -sinf(angle);
    matRotY.m[1][1] = 1.0f;
    matRotY.m[2][0] = sinf(angle);
    matRotY.m[2][2] = cosf(angle);
    matRotY.m[3][3] = 1.0f;
}

void Scene::rotateX(float angle) {
    matRotX.m[0][0] = 1.0f;
    matRotX.m[1][1] = cosf(angle);
    matRotX.m[1][2] = sinf(angle);
    matRotX.m[2][1] = -sinf(angle);
    matRotX.m[2][2] = cosf(angle);
    matRotX.m[3][3] = 1.0f;
}

void Scene::rotateZ(float angle) {
    matRotZ.m[0][0] = cosf(angle);
    matRotZ.m[0][1] = sinf(angle);
    matRotZ.m[1][0] = -sinf(angle);
    matRotZ.m[1][1] = cosf(angle);
    matRotZ.m[2][2] = 1.0f;
    matRotZ.m[3][3] = 1.0f;
}


void Scene::project() {
	float fNear = 0.1f;
	float fFar = 1000.0f;
	float fAspectRatio = (float)WIDTH / (float)HEIGHT;
	float fFovRad = 1.0f / tanf(FOV * 0.5f / 180.0f * 3.14159f);

	matProj.m[0][0] = fAspectRatio * fFovRad;
	matProj.m[1][1] = fFovRad;
	matProj.m[2][2] = fFar / (fFar - fNear);
	matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][3] = 0.0f;
}

void Scene::update() {
    rotateX(thetaX);
    rotateY(thetaY);
    rotateZ(thetaZ);
    translate(.5f+dx, .5f+dy, 3.0f+dz);
    scale(1.0f);
    matSRT = matScale * matRotX * matRotY * matRotZ * matTranslate;
}

void Scene::draw(uint8_t* bitmap) {
    for(auto tri : cube.tris) {
        Triangle srt;
        for(int i = 0; i < 3; ++i) {
            srt.p[i] = (tri.p[i] * matSRT);
        }
        if(isVisible(srt)) {
            Triangle proj;
            for(int i = 0; i < 3; ++i) {
                proj.p[i] = srt.p[i] * matProj;

            }
            drawTriangle(proj, bitmap);
        }
    }
}

void Scene::initCube() {
    cube.tris = {
        // SOUTH
		{ Vec3(-1.0f, -1.0f, -1.0f),    Vec3(-1.0f, 1.0f, -1.0f),    Vec3(1.0f, 1.0f, -1.0f) },
		{ Vec3(-1.0f, -1.0f, -1.0f),    Vec3(1.0f, 1.0f, -1.0f),    Vec3(1.0f, -1.0f, -1.0f) },
		{ Vec3(1.0f, -1.0f, -1.0f),    Vec3(1.0f, 1.0f, -1.0f),    Vec3(1.0f, 1.0f, 1.0f) }, //EAST
		{ Vec3(1.0f, -1.0f, -1.0f),    Vec3(1.0f, 1.0f, 1.0f),    Vec3(1.0f, -1.0f, 1.0f) },
		{ Vec3(1.0f, -1.0f, 1.0f),    Vec3(1.0f, 1.0f, 1.0f),    Vec3(-1.0f, 1.0f, 1.0f) }, //NORTH
		{ Vec3(1.0f, -1.0f, 1.0f),    Vec3(-1.0f, 1.0f, 1.0f),    Vec3(-1.0f, -1.0f, 1.0f) },
		{ Vec3(-1.0f, -1.0f, 1.0f),    Vec3(-1.0f, 1.0f, 1.0f),    Vec3(-1.0f, 1.0f, -1.0f) }, //WEST
		{ Vec3(-1.0f, -1.0f, 1.0f),    Vec3(-1.0f, 1.0f, -1.0f),    Vec3(-1.0f, -1.0f, -1.0f) },
		{ Vec3(-1.0f, 1.0f, -1.0f),    Vec3(-1.0f, 1.0f, 1.0f),    Vec3(1.0f, 1.0f, 1.0f) }, //TOP
		{ Vec3(-1.0f, 1.0f, -1.0f),    Vec3(1.0f, 1.0f, 1.0f),    Vec3(1.0f, 1.0f, -1.0f) },
		{ Vec3(1.0f, -1.0f, 1.0f),    Vec3(-1.0f, -1.0f, 1.0f),    Vec3(-1.0f, -1.0f, -1.0f) }, //BOTTOM
		{ Vec3(1.0f, -1.0f, 1.0f),    Vec3(-1.0f, -1.0f, -1.0f),    Vec3(1.0f, -1.0f, -1.0f) },
    };
};


void Scene::translate(float x, float y, float z) {
    matTranslate.m[0][0] = 1.0f;
    matTranslate.m[1][1] = 1.0f;
    matTranslate.m[2][2] = 1.0f;
    matTranslate.m[3][3] = 1.0f;
    matTranslate.m[3][0] = x;
    matTranslate.m[3][1] = y;
    matTranslate.m[3][2] = z;
}

void Scene::scale(float q) {
    matScale.m[0][0] = q;
    matScale.m[1][1] = q;
    matScale.m[2][2] = q;
    matScale.m[3][3] = 1.0f;
}

bool Scene::isVisible(const Triangle& tri) const {
    Vec3 line1 = tri.p[1] - tri.p[0];
    Vec3 line2 = tri.p[2] - tri.p[0];
    Vec3 normal = line1.crossProd(line2);
    
    return normal.dotProduct(tri.p[0]) < 0;
}
