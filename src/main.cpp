#include <glm/vec3.hpp>
#include <iostream>
#include "headers/raytracer.h"
#include "headers/constants.h"
#include <fstream>
#include <SFML/Graphics.hpp>

void displayPixelArray(glm::vec3 *pixels)
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);

    sf::Uint8 *color_arr = new sf::Uint8[WIDTH * HEIGHT * 4];
    int offset = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        glm::vec3 color = pixels[i];
        color_arr[offset] = floor(255 * color[0]);
        color_arr[offset + 1] = floor(255 * color[1]);
        color_arr[offset + 2] = floor(255 * color[2]);
        color_arr[offset + 3] = 255;
        offset += 4;
    }
    texture.update(color_arr);

    sf::Sprite viewport(texture);

    glm::vec3 dir(0, 0, 0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        window.clear(sf::Color(0, 0, 0));
        window.draw(viewport);
        window.display();
    }
}

int main()
{
    glm::vec3 *pixels = new glm::vec3[WIDTH * HEIGHT];
    raytracer::render(pixels);

    displayPixelArray(pixels);
    return 0;
}