#include "scene.h"

Scene::Scene() :
    thetaX(0), thetaY(0), thetaZ(0), dx(0), dy(0), dz(0), camAngleY(0), mode(COLORED), control(OBJECT)
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

Mtx44 Scene::rotateY(float angle) {
    Mtx44 out;
    out.m[0][0] = cosf(angle);
    out.m[0][2] = -sinf(angle);
    out.m[1][1] = 1.0f;
    out.m[2][0] = sinf(angle);
    out.m[2][2] = cosf(angle);
    out.m[3][3] = 1.0f;
    return out;
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
    matRotY = rotateY(thetaY);
    rotateZ(thetaZ);
    translate(dx, dy, 3.0f+dz);
    scale(1.0f);
    prepareCamera();
    prepareView();
    matSRT = matScale * matRotX * matRotY * matRotZ * matTranslate * matView;
    //matSRT = matView;
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
                proj.v[i].p.perspDiv();
            }
            proj.draw(mode, bitmap);
        }
    }
}

void Scene::initCube() {
    cube.tris = {
        // SOUTH
        { Vertex(Vec4(-1.0f, -1.0f, -1.0f, 1.0f), WHI),    Vertex(Vec4(-1.0f, 1.0f, -1.0f, 1.0f), WHI),    Vertex(Vec4(1.0f, 1.0f, -1.0f, 1.0f), WHI) },
        { Vertex(Vec4(-1.0f, -1.0f, -1.0f, 1.0f), WHI),    Vertex(Vec4(1.0f, 1.0f, -1.0f, 1.0f), WHI),    Vertex(Vec4(1.0f, -1.0f, -1.0f, 1.0f), WHI) },
        { Vertex(Vec4(1.0f, -1.0f, -1.0f, 1.0f), WHI),    Vertex(Vec4(1.0f, 1.0f, -1.0f, 1.0f), WHI),    Vertex(Vec4(1.0f, 1.0f, 1.0f, 1.0f), WHI) }, //EAST
        { Vertex(Vec4(1.0f, -1.0f, -1.0f, 1.0f), WHI),    Vertex(Vec4(1.0f, 1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec4(1.0f, -1.0f, 1.0f, 1.0f), WHI) },
        { Vertex(Vec4(1.0f, -1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec4(1.0f, 1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec4(-1.0f, 1.0f, 1.0f, 1.0f), WHI) }, //NORTH
        { Vertex(Vec4(1.0f, -1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec4(-1.0f, 1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec4(-1.0f, -1.0f, 1.0f, 1.0f), WHI) },
        { Vertex(Vec4(-1.0f, -1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec4(-1.0f, 1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec4(-1.0f, 1.0f, -1.0f, 1.0f), WHI) }, //WEST
        { Vertex(Vec4(-1.0f, -1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec4(-1.0f, 1.0f, -1.0f, 1.0f), WHI),    Vertex(Vec4(-1.0f, -1.0f, -1.0f, 1.0f), WHI) },
        { Vertex(Vec4(-1.0f, 1.0f, -1.0f, 1.0f), WHI),    Vertex(Vec4(-1.0f, 1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec4(1.0f, 1.0f, 1.0f, 1.0f), WHI) }, //TOP
        { Vertex(Vec4(-1.0f, 1.0f, -1.0f, 1.0f), WHI),    Vertex(Vec4(1.0f, 1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec4(1.0f, 1.0f, -1.0f, 1.0f), WHI) },
        { Vertex(Vec4(1.0f, -1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec4(-1.0f, -1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec4(-1.0f, -1.0f, -1.0f, 1.0f), WHI) }, //BOTTOM
		{ Vertex(Vec4(1.0f, -1.0f, 1.0f, 1.0f), WHI),    Vertex(Vec4(-1.0f, -1.0f, -1.0f, 1.0f), WHI),    Vertex(Vec4(1.0f, -1.0f, -1.0f, 1.0f), WHI) },
    };

    for(int k = 0; k < 12; ++k) {
        for(int i = 0; i < 3; ++i) {
            cube.tris[k].v[i].color.r = floatToInt(0, 255, -1.0f, 1.0f, cube.tris[k].v[i].p.x);
            cube.tris[k].v[i].color.g = floatToInt(0, 255, -1.0f, 1.0f, cube.tris[k].v[i].p.y);
            cube.tris[k].v[i].color.b = floatToInt(0, 255, -1.0f, 1.0f, cube.tris[k].v[i].p.z);
            cube.tris[k].v[i].color.a = 255;
        }
    }
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

void Scene::pointAt(Vec4& pos, Vec4& target, Vec4&  up) {
  // Calc new forward direction
    Vec4 newForward = (target - pos);
    newForward.normalize();

    Vec4 a = newForward * up.dotProduct(newForward);
    Vec4 newUp = (up - a);
    newUp.normalize();
    Vec4 newRight = newUp.xyzCrossProduct(newForward);

	matCamera.m[0][0] = newRight.x;	    matCamera.m[0][1] = newRight.y;	    matCamera.m[0][2] = newRight.z;	    matCamera.m[0][3] = 0.0f;
	matCamera.m[1][0] = newUp.x;		matCamera.m[1][1] = newUp.y;		matCamera.m[1][2] = newUp.z;		matCamera.m[1][3] = 0.0f;
	matCamera.m[2][0] = newForward.x;	matCamera.m[2][1] = newForward.y;	matCamera.m[2][2] = newForward.z;	matCamera.m[2][3] = 0.0f;
	matCamera.m[3][0] = pos.x;			matCamera.m[3][1] = pos.y;			matCamera.m[3][2] = pos.z;			matCamera.m[3][3] = 1.0f;
}

void Scene::prepareCamera() {
    /*
    lookDir = Vec4(.0f, .0f, 1.0f);
    Vec4 up = Vec4(.0f, 1.0f, .0f);
    Vec4 target = camera - lookDir;
    */
  
    Vec4 up = Vec4(.0f, 1.0f, .0f);
    Vec4 target = Vec4(.0f, .0f, 1.0f);
    lookDir = target * rotateY(camAngleY);
    target = camera + lookDir;
    pointAt(camera, target, up);
}

void Scene::prepareView() {
  matView = MatrixQuickInverse(matCamera);
}
