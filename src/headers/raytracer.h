#ifndef RAYTRACER_HEADER
#define RAYTRACER_HEADER

#include "../included/glm/vec3.hpp"
#include "shapes.h"
#include <vector>
#include "light.h"
#include "headers/screen.h"

namespace raytracer
{
    struct World
    {
        World(Screen& screen);

        Screen& m_screen;
        glm::vec3 camera_offset = glm::vec3(0, 0, 0);
        std::vector<Sphere> spheres;
        std::vector<Light> lights;

        glm::vec3 cast_ray(glm::vec3 orig, glm::vec3 dir, size_t depth);
        void render();
        bool scene_intersect(glm::vec3 orig, glm::vec3 dir, glm::vec3 &t0_out, glm::vec3 &normal_out, Material &material);
        void add_sphere(glm::vec3 center, int radius, Material material);
        void add_light(glm::vec3 pos, float intensity);
    };

} // namespace raytracer
#endif