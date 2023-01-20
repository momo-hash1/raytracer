#include <SFML/Graphics.hpp>
#include <glm/vec2.hpp>
#include <iostream>
#include "headers/raytracer.h"
#include "headers/constants.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    sf::Uint8 *pixels = new sf::Uint8[WIDTH * HEIGHT * 4];
    sf::Texture viewport_texture;
    viewport_texture.create(WIDTH, HEIGHT);
    sf::Sprite viewport(viewport_texture);
    viewport_texture.setSmooth(true);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        raytracer::render(pixels);
        viewport_texture.update(pixels);
        
        window.draw(viewport);
        window.display();
    }

    return 0;
}