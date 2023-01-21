#include <glm/vec3.hpp>
#include "shapes.h"
#include <SFML/Graphics.hpp>

namespace raytracer
{
    glm::vec3 cast_ray(glm::vec3 orig, glm::vec3 dir, Sphere sphere);
    void render(sf::Uint8 *pixels, glm::vec3 offest_dir);

} // namespace raytracer
