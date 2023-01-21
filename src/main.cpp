#include <glm/vec3.hpp>
#include <iostream>
#include "headers/raytracer.h"
#include "headers/constants.h"
#include <fstream>
#include <SFML/Graphics.hpp>


void displayPixelArray(sf::Uint8 *pixels)
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);

    texture.update(pixels);

    sf::Sprite viewport(texture);

    glm::vec3 offset_dir(0, 0, 0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                    offset_dir = offset_dir + glm::vec3(0, 0, -0.5);
                    break;
                case sf::Keyboard::S:
                    offset_dir = offset_dir + glm::vec3(0, 0, 0.5);
                    break;
                case sf::Keyboard::D:
                    offset_dir = offset_dir + glm::vec3(0.5, 0, 0);
                    break;
                case sf::Keyboard::A:
                    offset_dir = offset_dir + glm::vec3(-0.5, 0, 0);
                    break;
                }
                raytracer::render(pixels, offset_dir);

                texture.update(pixels);
            }
        }

        window.clear(sf::Color(0, 0, 0));
        window.draw(viewport);
        window.display();
    }
}

int main()
{
    sf::Uint8 *pixels = new sf::Uint8[WIDTH * HEIGHT * 4];
    raytracer::render(pixels, glm::vec3(0, 0, 0));

    displayPixelArray(pixels);
    return 0;
}