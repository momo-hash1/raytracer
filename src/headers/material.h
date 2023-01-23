#ifndef MATERIAL_HEADER
#define MATERIAL_HEADER

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/vec2.hpp>

struct Material
{
    glm::vec3 color;
    float specular;
    glm::vec2 albedo;
    Material(glm::vec3 _color, float _specular,
             glm::vec2 _albedo) : color(_color), specular(_specular), albedo(_albedo)
    {
    }
    Material() : albedo(glm::vec2(1, 1)){}
    glm::vec3 reflect(glm::vec3 light_dir, glm::vec3 normal)
    {
        return light_dir - normal * 2.f * glm::dot(light_dir, normal);
    }
};

#endif