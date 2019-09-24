#include "scene.h"


Scene::Scene() :
thetaX(0), thetaY(0), thetaZ(0), dx(0), dy(0), dz(0), mode(WIREFRAME)
{
    initCube();
    project();
};



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
	float fAspectRatio = (float)HEIGHT / (float)WIDTH;
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
        Triangle srt = tri;
        for(int i = 0; i < 3; ++i) {
            srt.v[i].p = (tri.v[i].p * matSRT);
        }
        srt.computeNorm();
        if(srt.norm.dotProduct(srt.v[0].p) < 0) {
            Triangle proj = srt;
            for(int i = 0; i < 3; ++i) {
                proj.v[i].p = srt.v[i].p * matProj;

            }
            proj.draw(mode, bitmap);
        }
    }
}

void Scene::initCube() {
    cube.tris = {
        // SOUTH
		{ Vertex(Vec3(0.0f, 0.0f, 0.0f), BLA),    Vertex(Vec3(0.0f, 1.0f, 0.0f), GRE),    Vertex(Vec3(1.0f, 1.0f, 0.0f), YEL) },
		{ Vertex(Vec3(0.0f, 0.0f, 0.0f), BLA),    Vertex(Vec3(1.0f, 1.0f, 0.0f), YEL),    Vertex(Vec3(1.0f, 0.0f, 0.0f), RED) },
		{ Vertex(Vec3(1.0f, 0.0f, 0.0f), RED),    Vertex(Vec3(1.0f, 1.0f, 0.0f), YEL),    Vertex(Vec3(1.0f, 1.0f, 1.0f), WHI) }, //EAST
		{ Vertex(Vec3(1.0f, 0.0f, 0.0f), RED),    Vertex(Vec3(1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec3(1.0f, 0.0f, 1.0f), PUR) },
		{ Vertex(Vec3(1.0f, 0.0f, 1.0f), PUR),    Vertex(Vec3(1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec3(0.0f, 1.0f, 1.0f), BLU) }, //NORTH
		{ Vertex(Vec3(1.0f, 0.0f, 1.0f), PUR),    Vertex(Vec3(0.0f, 1.0f, 1.0f), BLU),    Vertex(Vec3(0.0f, 0.0f, 1.0f), NAV) },
		{ Vertex(Vec3(0.0f, 0.0f, 1.0f), NAV),    Vertex(Vec3(0.0f, 1.0f, 1.0f), BLU),    Vertex(Vec3(0.0f, 1.0f, 0.0f), GRE) }, //WEST
		{ Vertex(Vec3(0.0f, 0.0f, 1.0f), NAV),    Vertex(Vec3(0.0f, 1.0f, 0.0f), GRE),    Vertex(Vec3(0.0f, 0.0f, 0.0f), BLA) },
		{ Vertex(Vec3(0.0f, 1.0f, 0.0f), GRE),    Vertex(Vec3(0.0f, 1.0f, 1.0f), BLU),    Vertex(Vec3(1.0f, 1.0f, 1.0f), WHI) }, //TOP
		{ Vertex(Vec3(0.0f, 1.0f, 0.0f), GRE),    Vertex(Vec3(1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec3(1.0f, 1.0f, 0.0f), YEL) },
		{ Vertex(Vec3(1.0f, 0.0f, 1.0f), PUR),    Vertex(Vec3(0.0f, 0.0f, 1.0f), NAV),    Vertex(Vec3(0.0f, 0.0f, 0.0f), BLA) }, //BOTTOM
		{ Vertex(Vec3(1.0f, 0.0f, 1.0f), PUR),    Vertex(Vec3(0.0f, 0.0f, 0.0f), BLA),    Vertex(Vec3(1.0f, 0.0f, 0.0f), RED) },
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

