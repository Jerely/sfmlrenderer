#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Test");
    sf::Image        image(800, 600, sf::Color(0, 0, 0));
    sf::Sprite       sprite;
    sf::Uint8        *pixels  = new sf::Uint8[800 * 600 * 4];

    while(window.IsOpened())
    {
        for(int x = 0; x < 800; x++)
        {
            for(int y = 0; y < 600; y++)
            {
                pixels[(y * x) * 4]     = 255; // R?
                pixels[(y * x) * 4 + 1] = 255; // G?
                pixels[(y * x) * 4 + 2] = 255; // B?
                pixels[(y * x) * 4 + 3] = 255; // A?
            }
        }

        image.LoadFromPixels(800, 600, pixels);
        sprite.SetImage(image);
        window.Draw(sprite);
        window.Display();
    }

    delete [] pixels;
    return 0;
}
