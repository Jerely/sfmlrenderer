#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

union Color {
    uint32_t u32color;
    struct U8color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
        void green() { r = 0; g = 255; b = 0; a = 255; }
    };
    U8color u8color;
};

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

const int WIDTH = 10;
const int HEIGHT = 10;

inline void setPixel(uint8_t* bitmap, uint32_t x, uint32_t y, Color color) {
    ((uint32_t*)bitmap)[x+y*WIDTH] = color.u32color;
}

void fillPixels(uint8_t* bitmap) {
    memset(bitmap, 0, WIDTH*HEIGHT*4);
    for(uint32_t y = 0; y < WIDTH; y++) {
        for(uint32_t x = 0; x < HEIGHT; x++) {
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

        fillPixels(bitmap);
        image.create(WIDTH, HEIGHT, bitmap); 
        texture.loadFromImage(image); 
        sprite.setTexture(texture);
        window.clear();
        sprite.setScale(20, 20);
        window.draw(sprite);
        window.display();
    }

    delete[] bitmap;
    return EXIT_SUCCESS;
}
