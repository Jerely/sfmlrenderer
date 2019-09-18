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

/*
plotLine(x0,y0, x1,y1)
  dx = x1 - x0
  dy = y1 - y0
  D = 2*dy - dx
  y = y0

  for x from x0 to x1
    plot(x,y)
    if D > 0
       y = y + 1
       D = D - 2*dx
    end if
    D = D + 2*dy
*/

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

void bresenham(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint8_t* bitmap) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int D = 2*dy - dx;
    int y = y0;
    for(int x = x0; x <= x1; ++x) {
        setPixel(bitmap, x, y, WHITE);
        if(D > 0) {
            ++y;
            D -= 2*dx;
        }
        D += 2*dy;
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
        bresenham(0, 0, 100, 50, bitmap);
        displayBitmap(window, bitmap);
        //scene.draw(window, bitmap);
    }

    delete[] bitmap;
    return EXIT_SUCCESS;
}
