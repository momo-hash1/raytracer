#include <glm/vec3.hpp>

struct Sphere
{
    glm::vec3 center;
    int radius;
    Sphere(glm::vec3 center, int radius) : center(center), radius(r) {}
    intersection(glm::vec3 orig, glm::vec3 dir);
};
