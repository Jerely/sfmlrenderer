#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "line.h"
#include "types.h"
#include "vec4.h"
#include "scene.h"
#include "timer.h"
#include "triangle.h"
#include <ctime>
#include <windows.h>
#include <iostream>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const float FOV = 90.0f;
const int SCALEW = 1;
const int SCALEH = 1;

static sf::Image image;
static sf::Texture texture;
static sf::Sprite sprite;

void displayBitmap(sf::RenderWindow& window, uint8_t* bitmap)
{
    image.create(WIDTH, HEIGHT, bitmap); 
    texture.loadFromImage(image); 
    sprite.setTexture(texture);
    sprite.setScale(SCALEW, SCALEH);
    window.clear();
    window.draw(sprite);
    window.display();
}

void fillPixels(uint8_t* bitmap, Color color)
{
    for(uint32_t y = 0; y < HEIGHT; y++) {
        for(uint32_t x = 0; x < WIDTH; x++) {
            setPixel(bitmap, x, y, color);
        }
    }
}

enum SCENE_OBJECT {
	CUBE, LIGHT0, LIGHT1, LIGHT2
};

enum LIGHT_PARAM {
	SPEC, EXP, BRIGHTNESS
};

void render(uint8_t* bitmap, Scene& scene, sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
		static Light* curLight = &(scene.rasterizer.light0);
		static const string objNameDict[]{ "cube", "light0", "light1", "light2" };
		static LIGHT_PARAM lightParam = SPEC; 

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            scene.rasterizer.perspectiveCorrect = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            scene.rasterizer.perspectiveCorrect = false;
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			scene.curMesh = CUBE;
			cout << "Current object is cube." << endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			curLight = &(scene.rasterizer.light0);
			scene.curMesh = LIGHT0;
			cout << "Current object is light0." << endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			curLight = &(scene.rasterizer.light1);
			scene.curMesh = LIGHT1;
			cout << "Current object is light1." << endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
			curLight = &(scene.rasterizer.light2);
			scene.curMesh = LIGHT2;
			cout << "Current object is light2." << endl;
		}
#define OPUT_COORDS \
			cout << objNameDict[scene.curMesh] \
			   	<< " x: " << scene.getCurMesh().x << \
				" y: " << scene.getCurMesh().y \
				<< " z: " << scene.getCurMesh().z << endl;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			scene.getCurMesh().z += 0.1f;
			if (scene.curMesh != CUBE) {
				curLight->pos.z += 0.1f;
			}
			OPUT_COORDS
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			scene.getCurMesh().z -= 0.1f;
			if (scene.curMesh != CUBE) {
				curLight->pos.z -= 0.1f;
			}
			OPUT_COORDS
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			scene.getCurMesh().x -= 0.1f;
			if (scene.curMesh != CUBE) {
				curLight->pos.x -= 0.1f;
			}
			OPUT_COORDS
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			scene.getCurMesh().x += 0.1f;
			if (scene.curMesh != CUBE) {
				curLight->pos.x += 0.1f;
			}
			OPUT_COORDS
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			scene.getCurMesh().y += 0.1f;
			if (scene.curMesh != CUBE) {
				curLight->pos.y += 0.1f;
			}
			OPUT_COORDS
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			scene.getCurMesh().y -= 0.1f;
			if (scene.curMesh != CUBE) {
				curLight->pos.y -= 0.1f;
			}
			OPUT_COORDS
		}
#define OPUT_ANGLE  \
			cout << "cube thetaX: " << scene.getCurMesh().thetaX \
				<< " thetaY: " << scene.getCurMesh().thetaY \
				<< " thetaZ: " << scene.getCurMesh().thetaZ << endl;

#define OPUT_LIGHT_DIR \
cout << objNameDict[scene.curMesh] << " dir x: " << curLight->dir.x \
		<< " y: " << curLight->dir.y << " z: " << curLight->dir.z << endl;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (scene.curMesh == CUBE) {
				scene.getCurMesh().thetaX += 0.1f;
				OPUT_ANGLE
			}
			else {
				curLight->dir.z += 0.1f;
				curLight->dir.normalize();
				OPUT_LIGHT_DIR
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (scene.curMesh == CUBE) {
				scene.getCurMesh().thetaX -= 0.1f;
				OPUT_ANGLE
			}
			else {
				curLight->dir.z -= .1f;
				curLight->dir.normalize();
				OPUT_LIGHT_DIR
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (scene.curMesh == CUBE) {
				scene.getCurMesh().thetaY -= 0.1f;
				OPUT_ANGLE
			}
			else {
				curLight->dir.x -= .1f;
				curLight->dir.normalize();
				OPUT_LIGHT_DIR
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (scene.curMesh == CUBE) {
				scene.getCurMesh().thetaY += 0.1f;
				OPUT_ANGLE
			}
			else {
				curLight->dir.x += .1f;
				curLight->dir.normalize();
				OPUT_LIGHT_DIR
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) {
			if (scene.curMesh == CUBE) {
				scene.getCurMesh().thetaZ += 0.1f;
				OPUT_ANGLE
			}
			else {
				curLight->dir.y += .1f;
				curLight->dir.normalize();
				OPUT_LIGHT_DIR
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
			if (scene.curMesh == CUBE) {
				scene.getCurMesh().thetaZ -= 0.1f;
				OPUT_ANGLE
			}
			else {
				curLight->dir.y -= .1f;
				curLight->dir.normalize();
				OPUT_LIGHT_DIR
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			lightParam = SPEC;
			cout << "cur param is spec\n";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			lightParam = EXP;
			cout << "cur param is exp\n";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
			lightParam = BRIGHTNESS;
			cout << "cur param is brightness\n";
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))) {
			if (lightParam == SPEC) {
				scene.rasterizer.mat.spec.w -= .5f;
				cout << "spec is " << scene.rasterizer.mat.spec.w << endl;
			}
			if (lightParam == EXP) {
				scene.rasterizer.exp -= .5f;
				scene.rasterizer.updateLights();
				cout << "exp is " << scene.rasterizer.exp << endl;
			}
			if (lightParam == BRIGHTNESS) {
				scene.rasterizer.brightness -= .2f;
				scene.rasterizer.updateLights();
				cout << "br is " << scene.rasterizer.brightness << endl;
			}
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))) {
			if (lightParam == SPEC) {
				scene.rasterizer.mat.spec.w += .5f;
				cout << "spec is " << scene.rasterizer.mat.spec.w << endl;
			}
			if (lightParam == EXP) {
				scene.rasterizer.exp += .5f;
				scene.rasterizer.updateLights();
				cout << "exp is " << scene.rasterizer.exp << endl;
			}
			if (lightParam == BRIGHTNESS) {
				scene.rasterizer.brightness += .05f;
				scene.rasterizer.updateLights();
				cout << "br is " << scene.rasterizer.brightness << endl;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			scene.rasterizer.mode = WIREFRAME;
			cout << "current raster mode is wireframe." << endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			scene.rasterizer.mode = PHONG;
			cout << "current raster mode is Phong." << endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
			scene.rasterizer.mode = GOURAUD;
			cout << "current raster mode is Gouraud." << endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			scene.rasterizer.mode = FLAT;
			cout << "current raster mode is flat." << endl;

		}
        if (event.type == sf::Event::Closed)
            window.close();
    }
    
    fillPixels(bitmap, BLA);
    scene.update();
    scene.draw();
    displayBitmap(window, bitmap);
}

int main()
{
    uint8_t* bitmap = new uint8_t[WIDTH*HEIGHT*4];
    sf::RenderWindow window(sf::VideoMode(WIDTH*SCALEW, HEIGHT*SCALEH), "SFML window");
    Scene scene(bitmap);
    Timer timer;
    while (window.isOpen())
    {
        timer.beginFrame = clock();
        render(bitmap, scene, window);
        timer.endFrame = clock();
        timer.calcFps();
        if(timer.ready) {
            //cout << "FPS: " << timer.frameRate << " Frame time: " <<  timer.avgFrameTimeMs << endl;
            char str[64] = {0};
            sprintf_s(str, "FPS: %.2f Frame time: %.2f\n", timer.frameRate, timer.avgFrameTimeMs);
            window.setTitle(str);
            timer.ready = false;
        }
    }
    delete[] bitmap;
    return EXIT_SUCCESS;
}
