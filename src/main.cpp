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

void fillPixels(uint8_t* bitmap, Color color) {
    for(uint32_t y = 0; y < HEIGHT; y++) {
        for(uint32_t x = 0; x < WIDTH; x++) {
            setPixel(bitmap, x, y, color);
        }
    }
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
            scene.curMesh = 0;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
            scene.curMesh = 1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            scene.getCurMesh().thetaY -= 0.1f;
        } 
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            scene.getCurMesh().thetaY += 0.1f;
        } 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            scene.getCurMesh().thetaX += 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            scene.getCurMesh().thetaX -= 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
            scene.getCurMesh().thetaZ -= 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            scene.getCurMesh().thetaZ += 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            scene.getCurMesh().x -= 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            scene.getCurMesh().x += 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            scene.getCurMesh().y -= 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            scene.getCurMesh().y += 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            scene.getCurMesh().z += 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            scene.getCurMesh().z -= 0.1f;
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
