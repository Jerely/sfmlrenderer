#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "line.h"
#include "types.h"
#include "vec4.h"
#include "scene.h"
#include "timer.h"
#include <ctime>
#include <windows.h>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;
const float FOV = 90.0f;
const int SCALEW = 1;
const int SCALEH = 1;

sf::RenderWindow* pWindow = NULL;

    static sf::Image image;
    static sf::Texture texture;
    static sf::Sprite sprite;

void displayBitmap(sf::RenderWindow& window, uint8_t* bitmap) {
    image.create(WIDTH, HEIGHT, bitmap); 
    texture.loadFromImage(image); 
    sprite.setTexture(texture);
    sprite.setScale(SCALEW, SCALEH);
    window.clear();
    window.draw(sprite);
    window.display();
}


void render(uint8_t* bitmap, Scene& scene, sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            scene.mode = WIREFRAME;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            scene.mode = COLORED;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            scene.control = OBJECT;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
            scene.control = CAMERA;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if(scene.control == OBJECT) {
                scene.thetaY -= 0.1f;
            }
            else {
                scene.camAngleY += 0.1f;
            }
        } 
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if(scene.control == OBJECT) {
                scene.thetaY += 0.1f;
            }
            else {
                scene.camAngleY -= 0.1f;
            }
        } 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            scene.thetaX += 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            scene.thetaX -= 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
            scene.thetaZ -= 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            scene.thetaZ += 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if(scene.control == OBJECT) {
                scene.dx -= 0.1f;
            }
            else {
                scene.camera.x -= 0.1f;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if(scene.control == OBJECT) {
                scene.dx += 0.1f;
            }
            else {
                scene.camera.x += 0.1f;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if(scene.control == OBJECT) {
                scene.dy -= 0.1f;
            }
            else {
                scene.camera.y -= 0.1f;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            if(scene.control == OBJECT) {
                scene.dy += 0.1f;
            }
            else {
                scene.camera.y += 0.1f;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if(scene.control == OBJECT) {
                scene.dz += 0.1f;
            }
            else {
                scene.camera += scene.lookDir;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if(scene.control == OBJECT) {
                scene.dz -= 0.1f;
            }
            else {
                scene.camera -= scene.lookDir;
            }
        }
        if (event.type == sf::Event::Closed)
            window.close();
    }
    
    fillPixels(bitmap, BLA);
    scene.update();
    scene.draw(bitmap);
    displayBitmap(window, bitmap);
}


int main()
{
    uint8_t* bitmap = new uint8_t[WIDTH*HEIGHT*4];
    sf::RenderWindow window(sf::VideoMode(WIDTH*SCALEW, HEIGHT*SCALEH), "SFML window");
    pWindow = &window;
    Scene scene;
    Timer timer;
    while (window.isOpen())
    {
        timer.beginFrame = clock();
        render(bitmap, scene, window);
        timer.endFrame = clock();
        timer.calcFps();
        if(timer.ready) {
            cout << "FPS: " << timer.frameRate << " Frame time: " <<  timer.avgFrameTimeMs << endl;
            timer.ready = false;
        }
    }
    delete[] bitmap;
    return EXIT_SUCCESS;
}
