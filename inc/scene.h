#pragma once
#include "types.h"
#include "vec4.h"
#include "line.h"
#include "triangle.h"
#include "mesh.h"
#include "mtx44.h"
#include "rasterizer.h"
#include <SFML/Graphics.hpp>
#include <vector>

extern const int WIDTH;
extern const int HEIGHT;
extern const float FOV;
extern const int SCALEW;
extern const int SCALEH;

struct Scene {
    Mtx44 matProj;

    std::vector<Mesh> meshes;
    int curMesh;
    Rasterizer rasterizer;

    void draw();
    void drawMesh(Mesh& mesh);
    void projectManually(const Vec4&, Vec4&); //for debug
    void project();
    void update();
    Scene(uint8_t*);
    Mesh& getCurMesh();
};

