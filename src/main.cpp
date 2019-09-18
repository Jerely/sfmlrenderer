#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "line.h"
#include "types.h"
#include "vec3d.h"
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

void plotLineLow(int x0, int y0, int x1, int y1, uint8_t* bitmap) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0) {
      yi = -1;
      dy = -dy;
    }
    int D = 2*dy - dx;
    int y = y0;
    for(int x = x0; x <= x1; ++x) {
        setPixel(bitmap, x, y, WHITE);
        if(D > 0) {
            y = y + yi;
            D = D - 2*dx;
        }
      D += 2*dy;
    }
}

void plotLineHigh(int x0, int y0, int x1, int y1, uint8_t* bitmap) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if(dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int D = 2*dx - dy;
    int x = x0;
    for(int y = y0; y <= y1; ++y) {
        setPixel(bitmap, x, y, WHITE);
        if(D > 0) {
            x += xi;
            D -= 2*dy;
        }
        D += 2*dx;
    }
}


#define abs(x) ((x) > 0 ? (x) : -(x))

void plotLine(int x0, int y0, int x1, int y1, uint8_t* bitmap) {
    if(abs(y1 - y0) < abs(x1 - x0)) {
        if(x0 > x1) {
            plotLineLow(x1, y1, x0, y0, bitmap);
        }
        else {
            plotLineLow(x0, y0, x1, y1, bitmap);
        }
    }
    else {
        if(y0 > y1) {
            plotLineHigh(x1, y1, x0, y0, bitmap);
        }
        else {
            plotLineHigh(x0, y0, x1, y1, bitmap);
        }
    }
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
            if (event.type == sf::Event::Closed)
                window.close();
        }
     
        fillPixels(bitmap, BLACK);
        plotLine(100, 50, 50, 75, bitmap);
        displayBitmap(window, bitmap);
        //scene.draw(window, bitmap);
    }

    delete[] bitmap;
    return EXIT_SUCCESS;
}
