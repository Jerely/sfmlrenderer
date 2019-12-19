#include "scene.h"

const uint32_t NEAR = 1.0f;
const uint32_t FAR = 1000.0f;

Scene::Scene(uint8_t* bitmap) :
    meshes{initCube(), initSquare(), initSquare(), initSquare()},
    curMesh(0),
    rasterizer(bitmap)
{
	meshes[1].x = rasterizer.light0.pos.x;
	meshes[1].y = rasterizer.light0.pos.y;
	meshes[1].z = rasterizer.light0.pos.z;
	meshes[2].x = rasterizer.light1.pos.x;
	meshes[2].y = rasterizer.light1.pos.y;
	meshes[2].z = rasterizer.light1.pos.z;
	meshes[3].x = rasterizer.light2.pos.x;
	meshes[3].y = rasterizer.light2.pos.y;
	meshes[3].z = rasterizer.light2.pos.z;
    matProj = Mtx44::project((float)WIDTH/(float)HEIGHT, NEAR, FAR, 45.0f);
};

void Scene::update()
{
    for(int i = 0; i < 4; ++i)
        meshes[i].update();
}

Mesh& Scene::getCurMesh()
{
    return meshes[curMesh];
}

void Scene::draw()
{
    for(int i = 0; i < 4; ++i)
        drawMesh(meshes[i]);
}

void Scene::drawMesh(Mesh& mesh)
{
    //for(int j = 0; j < mesh.tris.size(); ++j) {
    for(auto& srt : mesh.tris) {
        //#define srt mesh.tris[j]
        for(int i = 0; i < 3; ++i) {
            srt.v[i].wPos = (srt.v[i].lPos * mesh.matSRT);
        }
        srt.computeNorm();
        if(srt.norm.dotProduct(srt.v[0].wPos) < 0) {
            for(int i = 0; i < 3; ++i) {
                srt.v[i].p = srt.v[i].wPos * matProj;
                srt.v[i].p.perspDiv();
                srt.v[i].p.w = 1 / srt.v[i].p.w;
                //projectManually(srt.v[i].p, proj.v[i].p);
            }
                rasterizer.draw(srt, mesh.isAlwaysWireframe);
        }
    }
}

void Scene::projectManually(const Vec4& in, Vec4& out) //for debug
{
	float fAspectRatio = (float)HEIGHT / (float)WIDTH;
	float fFovRad = 1.0f / tanf(FOV * 0.5f / 180.0f * 3.14159f);
    out.x = in.x * fAspectRatio * fFovRad / in.z;
    out.y = in.y * fFovRad / in.z;
}

