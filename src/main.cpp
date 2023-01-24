#include <glm/vec3.hpp>
#include <iostream>
#include "headers/raytracer.h"
#include "headers/constants.h"
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>

void handle_key_input(sf::Event &event, sf::Texture &texture, raytracer::World &world, sf::Uint8 *pixels)
{
    switch (event.key.code)
    {
    case sf::Keyboard::W:
        world.camera_offset = world.camera_offset + glm::vec3(0, 0, -5);
        break;
    case sf::Keyboard::S:
        world.camera_offset = world.camera_offset + glm::vec3(0, 0, 5);
        break;
    case sf::Keyboard::D:
        world.camera_offset = world.camera_offset + glm::vec3(5, 0, 0);
        break;
    case sf::Keyboard::A:
        world.camera_offset = world.camera_offset + glm::vec3(-5, 0, 0);
        break;
    }
    world.render(pixels);

    texture.update(pixels);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    raytracer::World world;
    world.add_sphere(glm::vec3(-3,    0,   -6), 2, Material(glm::vec3(0.1, 0.5, 0.1), 1, 0.8));
    world.add_sphere(glm::vec3(-1.0, -1.5, -12), 2, Material(glm::vec3(0.1, 0.5, 0.1), 15, 0));
    world.add_light(glm::vec3(-20, 20, 20), 1.5);

    sf::Uint8 *pixels = new sf::Uint8[WIDTH * HEIGHT * 4];
    world.render(pixels);

    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);
    texture.update(pixels);

    sf::Sprite viewport(texture);

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
                handle_key_input(event, texture, world, pixels);
            }
        }

        window.clear(sf::Color(0, 0, 0));
        window.draw(viewport);
        window.display();
    }

    return 0;
}