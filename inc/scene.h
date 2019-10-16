#pragma once
#include "types.h"
#include "vec4.h"
#include "line.h"
#include "triangle.h"
#include "mesh.h"
#include "mtx44.h"
#include "camera.h"
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
    RenderingMode mode;

    void draw(uint8_t*);
    void drawMesh(const Mesh& mesh, uint8_t* bitmap);
    void projectManually(const Vec4&, Vec4&); //for debug
    void project();
    void update();
    Scene();
    Mesh& getCurMesh();
};

