#include <glm/vec3.hpp>
#include <iostream>
#include "headers/raytracer.h"
#include "headers/constants.h"
#include <fstream>
#include <SFML/Graphics.hpp>

void pixel_arr_to_texture(glm::vec3 *pixels, sf::Uint8 *color_arr)
{
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
}

void displayPixelArray(glm::vec3 *pixels)
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);

    sf::Uint8 *color_arr = new sf::Uint8[WIDTH * HEIGHT * 4];
    pixel_arr_to_texture(pixels, color_arr);
    texture.update(color_arr);

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
                    offset_dir = offset_dir + glm::vec3(0, 0, -1);
                    break;
                case sf::Keyboard::S:
                    offset_dir = offset_dir + glm::vec3(0, 0, 1);
                    break;
                case sf::Keyboard::D:
                    offset_dir = offset_dir + glm::vec3(1, 0, 0);
                    break;
                case sf::Keyboard::A:
                    offset_dir = offset_dir + glm::vec3(-1, 0, 0);
                    break;
                }
                raytracer::render(pixels, offset_dir);

                pixel_arr_to_texture(pixels, color_arr);
                texture.update(color_arr);
            }
        }

        window.clear(sf::Color(0, 0, 0));
        window.draw(viewport);
        window.display();
    }
}

int main()
{
    glm::vec3 *pixels = new glm::vec3[WIDTH * HEIGHT];
    raytracer::render(pixels, glm::vec3(0, 0, 0));

    displayPixelArray(pixels);
    return 0;
}