#include "headers/constants.h"
#include <cmath>
#include <glm/vec3.hpp>
#include <limits>
#include "headers/raytracer.h"
using namespace raytracer;

glm::vec3 World::cast_ray(glm::vec3 orig, glm::vec3 dir)
{
    float t0 = std::numeric_limits<float>::max();
    if (!spheres[0].intersection(orig, dir, t0))
    {
        return glm::vec3(0, 0, 0);
    }
    return glm::vec3(1, 1, 1);
}

void World::render(sf::Uint8 *pixels)
{
    float fov = M_PI / 2;
    float c_tan = tan(fov / 2.);
    int offset = 0;
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            float x = (2 * (i + 0.5) / (float)WIDTH - 1) * c_tan * WIDTH / (float)HEIGHT;
            float y = -(2 * (j + 0.5) / (float)HEIGHT - 1) * c_tan;

            glm::vec3 dir = glm::vec3(x, y, -1) + camera_offset;
            dir = glm::normalize(dir);
            glm::vec3 color = World::cast_ray(glm::vec3(0, 0, 0), dir);

            pixels[offset] = floor(255 * color[0]);
            pixels[offset + 1] = floor(255 * color[1]);
            pixels[offset + 2] = floor(255 * color[2]);
            pixels[offset + 3] = 255;
            offset += 4;
        }
    }
}

void World::scene_intersect(glm::vec3 orig, glm::vec3 dir)
{
}

void World::add_sphere(glm::vec3 center, int radius)
{
    spheres.push_back(Sphere(center, radius));
}
