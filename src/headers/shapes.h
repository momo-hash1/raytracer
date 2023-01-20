#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

struct Sphere
{
    glm::vec3 center;
    int radius;
    Sphere(glm::vec3 center, int radius) : center(center), radius(radius) {}
    bool intersection(glm::vec3 orig, glm::vec3 dir, float &t0)
    {
        glm::vec3 L = center - orig;
        float tca = glm::dot(L, dir);
        float d2 = glm::dot(L, L) - tca * tca;
        if (d2 > radius * radius)
            return false;
        float thc = sqrtf(radius * radius - d2);
        t0 = tca - thc;
        float t1 = tca + thc;
        if (t0 < 0)
            t0 = t1;
        if (t0 < 0)
            return false;
        return true;
    };
};
