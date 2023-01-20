#include <glm/vec3.hpp>
#include "shapes.h"

namespace raytracer
{
    glm::vec3 cast_ray(glm::vec3 orig, glm::vec3 dir, Sphere sphere);
    void render(glm::vec3 *pixels);

} // namespace raytracer
