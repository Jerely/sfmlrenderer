#include "scene.h"

Scene::Scene() :
    meshes{initCube(), initSquare()},
    curMesh(0),
    mode(COLORED) 
{
    matProj = Mtx44::project((float)WIDTH/(float)HEIGHT, 1.0f, 1000.0f, 45.0f);
};

void Scene::update()
{
    for(int i = 0; i < 2; ++i)
        meshes[i].update();
}

Mesh& Scene::getCurMesh()
{
    return meshes[curMesh];
}

void Scene::draw(uint8_t* bitmap)
{
    for(int i = 0; i < 2; ++i)
        drawMesh(meshes[i], bitmap);
}

void Scene::drawMesh(const Mesh& mesh, uint8_t* bitmap)
{
    for(auto tri : mesh.tris) {
        Triangle srt = tri;
        for(int i = 0; i < 3; ++i) {
            srt.v[i].p = (tri.v[i].p * mesh.matSRT);
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

void Scene::projectManually(const Vec4& in, Vec4& out) //for debug
{
	float fAspectRatio = (float)HEIGHT / (float)WIDTH;
	float fFovRad = 1.0f / tanf(FOV * 0.5f / 180.0f * 3.14159f);
    out.x = in.x * fAspectRatio * fFovRad / in.z;
    out.y = in.y * fFovRad / in.z;
}

