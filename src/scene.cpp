#include "scene.h"

Scene::Scene() :
    thetaX(0),
    thetaY(0),
    thetaZ(0),
    dx(0),
    dy(0),
    dz(0),
    mode(COLORED) 
{
    initCube();
    initSquare();
    matProj.project((float)WIDTH/(float)HEIGHT, 1.0f, 1000.0f, 30.0f);
};

void fillPixels(uint8_t* bitmap, Color color) {
    for(uint32_t y = 0; y < HEIGHT; y++) {
        for(uint32_t x = 0; x < WIDTH; x++) {
            setPixel(bitmap, x, y, color);
        }
    }
}

void Scene::update() {
    matRotX.rotateX(thetaX);
    matRotY.rotateY(thetaY);
    matRotZ.rotateZ(thetaZ);
    matTranslate.translate(dx, dy, 3.0f+dz);
    matScale.scale(1.0f);
    matSRT = matScale * matRotX * matRotY * matRotZ * matTranslate;
    //matSRT = matScale * matTranslate;
}

void Scene::draw(uint8_t* bitmap) {
    drawMesh(cube, bitmap);
}

void Scene::drawMesh(const Mesh& mesh, uint8_t* bitmap) {
    for(auto tri : mesh.tris) {
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
                //projectManually(srt.v[i].p, proj.v[i].p);
            }
            proj.draw(mode, bitmap);
        }
    }
}

void Scene::initSquare() {
    square.tris = 
        {
         { Vertex(Vec4(-1.0f, 1.0f, 1.0f), RED), Vertex(Vec4(1.0f, 1.0f, 1.0f), GRE), Vertex(Vec4(-1.0f, -1.0f, 1.0f), WHI) },
         { Vertex(Vec4(-1.0f, -1.0f, 1.0f), WHI), Vertex(Vec4(1.0f, 1.0f, 1.0f), GRE), Vertex(Vec4(1.0f, -1.0f, 1.0f), BLU) }
        };
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

void Scene::scale(float q) {
    matScale.m[0][0] = q;
    matScale.m[1][1] = q;
    matScale.m[2][2] = q;
    matScale.m[3][3] = 1.0f;
}

void Scene::projectManually(const Vec4& in, Vec4& out) //for debug
{
	float fAspectRatio = (float)HEIGHT / (float)WIDTH;
	float fFovRad = 1.0f / tanf(FOV * 0.5f / 180.0f * 3.14159f);
    out.x = in.x * fAspectRatio * fFovRad / in.z;
    out.y = in.y * fFovRad / in.z;
}
    
