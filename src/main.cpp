#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "line.h"


const int WIDTH = 800;
const int HEIGHT = 600;

void fillPixels(uint8_t* bitmap) {
    memset(bitmap, 0, WIDTH*HEIGHT*4);
    for(uint32_t y = 0; y < HEIGHT; y++) {
        for(uint32_t x = 0; x < WIDTH; x++) {
            Color green;
            green.u8color.green();
            setPixel(bitmap, x, y, green);
        }
    }
}


int main()
{
    sf::Sprite sprite;
    sf::Image image;
    uint8_t* bitmap = new uint8_t[WIDTH*HEIGHT*4];

    sf::RenderWindow window(sf::VideoMode(WIDTH*4, HEIGHT*4), "SFML window");
    sf::Texture texture;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //fillPixels(bitmap);
        Color green;
        green.u8color.green();
        memset(bitmap, 255, WIDTH*HEIGHT*4);
        line(13, 20, 400, 200, bitmap, green);
        image.create(WIDTH, HEIGHT, bitmap); 
        texture.loadFromImage(image); 
        sprite.setTexture(texture);
        window.clear();
        window.draw(sprite);
        window.display();
    }

    delete[] bitmap;
    return EXIT_SUCCESS;
}
