#include <glm/vec3.hpp>
#include "shapes.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace raytracer
{
    struct World
    {
        glm::vec3 camera_offset = glm::vec3(0, 0, 0);
        std::vector<Sphere> spheres;

        glm::vec3 cast_ray(glm::vec3 orig, glm::vec3 dir);
        void render(sf::Uint8 *pixels);
        void scene_intersect(glm::vec3 orig, glm::vec3 dir);
        void add_sphere(glm::vec3 center, int radius);
    };

} // namespace raytracer
