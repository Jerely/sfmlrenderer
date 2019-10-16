#include "mesh.h"


Mesh initSquare()
{
    Mesh out;
    out.tris =
        {
         { Vertex(Vec4(-1.0f, 1.0f, 1.0f), RED), Vertex(Vec4(1.0f, 1.0f, 1.0f), GRE), Vertex(Vec4(-1.0f, -1.0f, 1.0f), WHI) },
         { Vertex(Vec4(-1.0f, -1.0f, 1.0f), WHI), Vertex(Vec4(1.0f, 1.0f, 1.0f), GRE), Vertex(Vec4(1.0f, -1.0f, 1.0f), BLU) }
        };
    return out;
}


Mesh initCube()
{
    Mesh out;
    out.tris = {
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
            out.tris[k].v[i].color.r = floatToInt(0, 255, -1.0f, 1.0f, out.tris[k].v[i].p.x);
            out.tris[k].v[i].color.g = floatToInt(0, 255, -1.0f, 1.0f, out.tris[k].v[i].p.y);
            out.tris[k].v[i].color.b = floatToInt(0, 255, -1.0f, 1.0f, out.tris[k].v[i].p.z);
            out.tris[k].v[i].color.a = 255;
        }
    }
    return out;
}

void Mesh::update()
{
    matScale = Mtx44::scale(1.0f);
    matRotX = Mtx44::rotateX(thetaX);
    matRotY = Mtx44::rotateY(thetaY);
    matRotZ = Mtx44::rotateZ(thetaZ);
    matTranslate = Mtx44::translate(dx, dy, 3.0f+dz);
    matSRT = matScale * matRotX * matRotY * matRotZ * matTranslate;
}
