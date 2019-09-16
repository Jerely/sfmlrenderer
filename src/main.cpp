#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

const int WIDTH = 10;
const int HEIGHT = 10;

void fillPixels(uint8_t* pixels) {
    memset(pixels, 0, WIDTH*HEIGHT*4);
    for(uint32_t x = 0; x < WIDTH; x++) {
        for(uint32_t y = 0; y < HEIGHT; y++) {
            pixels[4*(y + x*WIDTH)+0] = 0;   //R
            pixels[4*(y + x*WIDTH)+1] = 255; //G
            pixels[4*(y + x*WIDTH)+2] = 0;   //B
            pixels[4*(y + x*WIDTH)+3] = 255; //A
        }
    }
}

int main()
{
    sf::Sprite sprite;
    sf::Image image;
    uint8_t* pixels = new uint8_t[WIDTH*HEIGHT*4];

    sf::RenderWindow window(sf::VideoMode(WIDTH*20, HEIGHT*20), "SFML window");
    sf::Texture texture;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        fillPixels(pixels);
        image.create(WIDTH, HEIGHT, pixels); 
        texture.loadFromImage(image); 
        sprite.setTexture(texture);
        window.clear();
        sprite.setScale(20, 20);
        window.draw(sprite);
        window.display();
    }

    delete[] pixels;
    return EXIT_SUCCESS;
}
