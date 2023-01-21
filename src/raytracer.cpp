#include "headers/raytracer.h"
#include "headers/constants.h"
#include <cmath>
#include <glm/vec3.hpp>
#include <limits>

glm::vec3 raytracer::cast_ray(glm::vec3 orig, glm::vec3 dir, Sphere sphere)
{
    float t0 = std::numeric_limits<float>::max();
    if (!sphere.intersection(orig, dir, t0))
    {
        return glm::vec3(0, 0, 0);
    }
    return glm::vec3(1, 1, 1);
}
void raytracer::render(sf::Uint8 *pixels, glm::vec3 offset_dir)
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

            glm::vec3 dir = glm::vec3(x, y, -1) + offset_dir;
            dir = glm::normalize(dir);
            glm::vec3 color = cast_ray(glm::vec3(0, 0, 0), dir, Sphere(glm::vec3(0, 0, -16), 2));

            pixels[offset] = floor(255 * color[0]);
            pixels[offset + 1] = floor(255 * color[1]);
            pixels[offset + 2] = floor(255 * color[2]);
            pixels[offset + 3] = 255;
            offset += 4;
        }
    }
}