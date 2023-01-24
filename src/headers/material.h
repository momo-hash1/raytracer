#ifndef MATERIAL_HEADER
#define MATERIAL_HEADER

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/vec2.hpp>

struct Material
{
    glm::vec3 color;
    float specular;
    float reflect_ratio;
    Material(glm::vec3 _color, float _specular,
              float _reflect) : color(_color), specular(_specular), reflect_ratio(_reflect)
    {
    }
    Material() : specular(0){}
};

inline glm::vec3 _reflect(glm::vec3 light_dir, glm::vec3 normal)
{
    return light_dir - normal * 2.f * glm::dot(light_dir, normal);
}
#endif