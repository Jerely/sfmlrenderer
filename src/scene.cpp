#include "scene.h"
#include "line.h"
#include "triangle.h"

Scene::Scene():
    matProj({0}),
    matRotZ({0}),
    matRotX({0})
{
    initCube();
    populateProj();
};

void MultiplyMatrixVector(Vec3 &i, Vec3 &o, Mtx44 &m) {
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f)
	{
		o.x /= w; o.y /= w; o.z /= w;
	}
}

void fillPixels(uint8_t* bitmap, Color color) {
    for(uint32_t y = 0; y < HEIGHT; y++) {
        for(uint32_t x = 0; x < WIDTH; x++) {
            setPixel(bitmap, x, y, color);
        }
    }
}

void Scene::rotateX(float angle) {
    matRotX.m[0][0] = 1.0f;
    matRotX.m[1][1] = cosf(angle);
    matRotX.m[1][2] = sinf(angle);
    matRotX.m[2][1] = -sinf(angle);
    matRotX.m[2][2] = cosf(angle);
    matRotX.m[3][3] = 1.0f;
}


void Scene::populateProj() {
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

void Scene::draw(uint8_t* bitmap) {
    for(auto tri : cube.tris) {
        Triangle prepared;
        prepare(tri, prepared);
        drawTriangle(prepared, bitmap);
    }
}

void Scene::prepare(Triangle& inTri, Triangle& outTri) {
    /*
    Triangle triTranslated;
    // Offset into the screen
	triTranslated = inTri;
	triTranslated.p[0].z = inTri.p[0].z + 3.0f;
	triTranslated.p[1].z = inTri.p[1].z + 3.0f;
	triTranslated.p[2].z = inTri.p[2].z + 3.0f;

	triTranslated.p[0].x = inTri.p[0].x + .5f;
	triTranslated.p[1].x = inTri.p[1].x + .5f;
	triTranslated.p[2].x = inTri.p[2].x + .5f;

	triTranslated.p[0].y = inTri.p[0].y + .5f;
	triTranslated.p[1].y = inTri.p[1].y + .5f;
	triTranslated.p[2].y = inTri.p[2].y + .5f;

    //Rotate

    rotateX(0.0f);

	MultiplyMatrixVector(triTranslated.p[0], triTranslated.p[0], matRotX);
	MultiplyMatrixVector(triTranslated.p[1], triTranslated.p[1], matRotX);
	MultiplyMatrixVector(triTranslated.p[2], triTranslated.p[2], matRotX);

	MultiplyMatrixVector(triTranslated.p[0], triTranslated.p[0], matRotZ);
	MultiplyMatrixVector(triTranslated.p[1], triTranslated.p[1], matRotZ);
	MultiplyMatrixVector(triTranslated.p[2], triTranslated.p[2], matRotZ);

	// Project triangles from 3D --> 2D
	MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
	MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
	MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);
    */

    Vec3 shift(.5f, .5f, 3.0f);
    for(int i = 0; i < 3; ++i) {
        outTri.p[i] = (inTri.p[i] * .9f) + shift;
    	MultiplyMatrixVector(outTri.p[i], outTri.p[i], matProj);
    }

}

void Scene::initCube() {
    cube.tris = {
        // SOUTH
		{ Vec3(0.0f, 0.0f, 0.0f),    Vec3(0.0f, 1.0f, 0.0f),    Vec3(1.0f, 1.0f, 0.0f) },
		{ Vec3(0.0f, 0.0f, 0.0f),    Vec3(1.0f, 1.0f, 0.0f),    Vec3(1.0f, 0.0f, 0.0f) },
		{ Vec3(1.0f, 0.0f, 0.0f),    Vec3(1.0f, 1.0f, 0.0f),    Vec3(1.0f, 1.0f, 1.0f) }, //EAST
		{ Vec3(1.0f, 0.0f, 0.0f),    Vec3(1.0f, 1.0f, 1.0f),    Vec3(1.0f, 0.0f, 1.0f) },
		{ Vec3(1.0f, 0.0f, 1.0f),    Vec3(1.0f, 1.0f, 1.0f),    Vec3(0.0f, 1.0f, 1.0f) }, //NORTH
		{ Vec3(1.0f, 0.0f, 1.0f),    Vec3(0.0f, 1.0f, 1.0f),    Vec3(0.0f, 0.0f, 1.0f) },
		{ Vec3(0.0f, 0.0f, 1.0f),    Vec3(0.0f, 1.0f, 1.0f),    Vec3(0.0f, 1.0f, 0.0f) }, //WEST
		{ Vec3(0.0f, 0.0f, 1.0f),    Vec3(0.0f, 1.0f, 0.0f),    Vec3(0.0f, 0.0f, 0.0f) },
		{ Vec3(0.0f, 1.0f, 0.0f),    Vec3(0.0f, 1.0f, 1.0f),    Vec3(1.0f, 1.0f, 1.0f) }, //TOP
		{ Vec3(0.0f, 1.0f, 0.0f),    Vec3(1.0f, 1.0f, 1.0f),    Vec3(1.0f, 1.0f, 0.0f) },
		{ Vec3(1.0f, 0.0f, 1.0f),    Vec3(0.0f, 0.0f, 1.0f),    Vec3(0.0f, 0.0f, 0.0f) }, //BOTTOM
		{ Vec3(1.0f, 0.0f, 1.0f),    Vec3(0.0f, 0.0f, 0.0f),    Vec3(1.0f, 0.0f, 0.0f) },
    };
};

