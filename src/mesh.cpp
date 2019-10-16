#include "mesh.h"


Mesh initSquare()
{
    Mesh out;
    out.tris =
        {
         { Vertex(Vec4(-1.0f, 1.0f, 1.0f), RED), Vertex(Vec4(1.0f, 1.0f, 1.0f), GRE), Vertex(Vec4(-1.0f, -1.0f, 1.0f), WHI) },
         { Vertex(Vec4(-1.0f, -1.0f, 1.0f), WHI), Vertex(Vec4(1.0f, 1.0f, 1.0f), GRE), Vertex(Vec4(1.0f, -1.0f, 1.0f), BLU) }
        };
    out.scale = 0.1f;
    out.thetaX = 0;
    out.thetaY = 0;
    out.thetaZ = 0;
    out.x = -2.0f;
    out.y = 2.0f;
    out.z = 6.0f;
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
    out.scale = 1.0f;
    out.thetaX = -0.7f;
    out.thetaY = 0.7f;
    out.thetaZ = 0;
    out.x = 0;
    out.y = 0;
    out.z = 6.0f;
    return out;
}

void Mesh::update()
{
    matScale = Mtx44::scale(scale);
    matRotX = Mtx44::rotateX(thetaX);
    matRotY = Mtx44::rotateY(thetaY);
    matRotZ = Mtx44::rotateZ(thetaZ);
    matTranslate = Mtx44::translate(x, y, z);
    matSRT = matScale * matRotX * matRotY * matRotZ * matTranslate;
}
