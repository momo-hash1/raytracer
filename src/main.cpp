#include "../included/glm/vec3.hpp"
#include <iostream>
#include "headers/raytracer.h"
#include "headers/constants.h"
#include <vector>
#include <fstream>
#include "headers/screen.h"
#include <array>


int main()
{

    Material glass = Material(glm::vec3(0.0, 0.0, 0.0), .125, 0, 0.8);
    Material solid = Material(glm::vec3(0.1, 0.5, 0.1), 15, 0,0);

    Screen screen(WIDTH, HEIGHT);
    raytracer::World world(screen);

    world.add_sphere(glm::vec3(-3, 0, -6), 2, glass);
    world.add_sphere(glm::vec3(-1.0, -1.5, -12), 2, solid);
    world.add_light(glm::vec3(-20, 20, 20), 1.5);

    world.render();
    screen.dumpToFile("first");

    return 0;
}