#ifndef MATERIAL_HEADER
#define MATERIAL_HEADER

#include "../included/glm/vec3.hpp"
#include "../included/glm/geometric.hpp"
#include "../included/glm/vec2.hpp"
#include <algorithm>

struct Material
{
    glm::vec3 color;
    float specular;
    float reflect_ratio;
    float refract;
    Material(glm::vec3 _color, float _specular,
             float _reflect, float _refract) : color(_color),
                                               specular(_specular), reflect_ratio(_reflect),
                                               refract(_refract)
    {
    }
    Material() : specular(0) {}
};

#endif