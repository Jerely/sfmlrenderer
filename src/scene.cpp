#include "scene.h"
#include "line.h"
#include "triangle.h"

Scene::Scene() {
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

void Scene::update(float fElapsedTime) {
	fTheta += 1.0f * fElapsedTime;

	// Rotation Z
	matRotZ.m[0][0] = cosf(fTheta);
	matRotZ.m[0][1] = sinf(fTheta);
	matRotZ.m[1][0] = -sinf(fTheta);
	matRotZ.m[1][1] = cosf(fTheta);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;

	// Rotation X
	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cosf(fTheta * 0.5f);
	matRotX.m[1][2] = sinf(fTheta * 0.5f);
	matRotX.m[2][1] = -sinf(fTheta * 0.5f);
	matRotX.m[2][2] = cosf(fTheta * 0.5f);
	matRotX.m[3][3] = 1;
};

void Scene::populateProj() {
	float fNear = 0.1f;
	float fFar = 1000.0f;
	float fAspectRatio = (float)HEIGHT / (float)WIDTH;
	float fFovRad = 1.0f / tanf(FOV * 0.5f / 180.0f * 3.14159f);

    matProj = {0};
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

void Scene::prepare(Triangle& inTri, Triangle& triProjected) {
    Triangle triTranslated;
    // Offset into the screen
	triTranslated = inTri;
	triTranslated.p[0].z = inTri.p[0].z + 3.0f;
	triTranslated.p[1].z = inTri.p[1].z + 3.0f;
	triTranslated.p[2].z = inTri.p[2].z + 3.0f;

	// Project triangles from 3D --> 2D
	MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
	MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
	MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);

	// Scale into view
    /*
	triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
	triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
	triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
	triProjected.p[0].x *= 0.5f * (float)WIDTH;
	triProjected.p[0].y *= 0.5f * (float)HEIGHT;
	triProjected.p[1].x *= 0.5f * (float)WIDTH;
	triProjected.p[1].y *= 0.5f * (float)HEIGHT;
	triProjected.p[2].x *= 0.5f * (float)WIDTH;
	triProjected.p[2].y *= 0.5f * (float)HEIGHT;
    */
}

void Scene::initCube() {
    cube.tris = {
        // SOUTH
		{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		// EAST                                                      
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

		// NORTH                                                     
		{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

		// WEST                                                      
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

		// TOP                                                       
		{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

		// BOTTOM                                                    
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
    };
};

