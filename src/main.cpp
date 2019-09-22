#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "line.h"
#include "types.h"
#include "vec3.h"
#include "scene.h"

const int WIDTH = 200;
const int HEIGHT = 200;
const float FOV = 90.0f;
const int SCALEW = 4;
const int SCALEH = 4;


void displayBitmap(sf::RenderWindow& window, uint8_t* bitmap) {
    static sf::Image image;
    static sf::Texture texture;
    static sf::Sprite sprite;

    image.create(WIDTH, HEIGHT, bitmap); 
    texture.loadFromImage(image); 
    sprite.setTexture(texture);
    sprite.setScale(SCALEW, SCALEH);
    window.clear();
    window.draw(sprite);
    window.display();
}



int main()
{
    uint8_t* bitmap = new uint8_t[WIDTH*HEIGHT*4];
    sf::RenderWindow window(sf::VideoMode(WIDTH*SCALEW, HEIGHT*SCALEH), "SFML window");
    Scene scene;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                scene.thetaX += 0.1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                scene.thetaX -= 0.1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                scene.thetaZ -= 0.1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                scene.thetaZ += 0.1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                scene.dx -= 0.1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                scene.dx += 0.1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                scene.dy += 0.1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                scene.dy -= 0.1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                scene.dz += 0.1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                scene.dz -= 0.1f;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }
     
        fillPixels(bitmap, BLACK);
        scene.update();
        scene.draw(bitmap);
        displayBitmap(window, bitmap);
    }

    delete[] bitmap;
    return EXIT_SUCCESS;
}
