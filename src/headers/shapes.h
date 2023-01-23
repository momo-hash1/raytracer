#ifndef SHAPES_HEADER
#define SHAPES_HEADER

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "material.h"

struct Sphere
{
    glm::vec3 center;
    int radius;
    Material material;
    int d_radius;
    Sphere(glm::vec3 _center,
           int _radius, Material _material) : center(_center), radius(_radius),
                                              material(_material), d_radius(radius * radius)
    {
    }
    bool intersection(glm::vec3 orig, glm::vec3 dir, float &t0)
    {
        glm::vec3 L = center - orig;
        float tca = glm::dot(L, dir);
        float d2 = glm::dot(L, L) - tca * tca;
        if (d2 > d_radius)
            return false;
        float thc = sqrtf(d_radius - d2);
        t0 = tca - thc;
        float t1 = tca + thc;
        if (t0 < 0)
            t0 = t1;
        if (t0 < 0)
            return false;
        return true;
    };
};
#endif