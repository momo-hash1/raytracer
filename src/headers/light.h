#include <glm/vec3.hpp>

struct Light
{
    glm::vec3 position;
    float intensity;
    Light(glm::vec3 _position, float _intensity){
        position = _position;
        intensity = _intensity;
    }
};
