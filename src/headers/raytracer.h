#include <glm/vec3.hpp>
#include "shapes.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "light.h"

namespace raytracer
{
    struct World
    {
        glm::vec3 camera_offset = glm::vec3(0, 0, 0);
        std::vector<Sphere> spheres;
        std::vector<Light> lights;

        glm::vec3 cast_ray(glm::vec3 orig, glm::vec3 dir);
        void render(sf::Uint8 *pixels);
        bool scene_intersect(glm::vec3 orig, glm::vec3 dir, glm::vec3 &t0_out, glm::vec3 &normal_out, glm::vec3 &color_out);
        void add_sphere(glm::vec3 center, int radius, glm::vec3 color);
        void add_light(glm::vec3 pos, float intensity);
    };

} // namespace raytracer
