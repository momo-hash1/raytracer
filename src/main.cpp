#include <glm/vec3.hpp>
#include <iostream>
#include "headers/raytracer.h"
#include "headers/constants.h"

int main()
{
    glm::vec3 *pixels = new glm::vec3[WIDTH * HEIGHT];
    raytracer::render(pixels);

    return 0;
}