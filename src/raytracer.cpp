#include "headers/constants.h"
#include <cmath>
#include <glm/vec3.hpp>
#include <limits>
#include <algorithm>
#include <iostream>
#include "headers/raytracer.h"
#include "headers/material.h"

using namespace raytracer;

glm::vec3 World::cast_ray(glm::vec3 orig, glm::vec3 dir)
{
    glm::vec3 t0, normal;
    Material material;
    float diffuse_light = 0;
    float specular = 0;
    if (!scene_intersect(orig, dir, t0, normal, material))
    {
        return glm::vec3(0, 0, 0);
    }

    for (size_t i = 0; i < lights.size(); i++)
    {
        glm::vec3 light_dir = glm::normalize(lights[i].position - t0);
        diffuse_light += lights[i].intensity * std::max(0.f, glm::dot(light_dir, normal));
        specular += powf(std::max(0.f, glm::dot(_reflect(light_dir, normal), dir)), material.specular) * lights[i].intensity;
    }
    
    return material.color * diffuse_light + 0.1f *specular;
}

void World::render(sf::Uint8 *pixels)
{
    float fov = M_PI / 2;
    float c_tan = tan(fov / 2.);
    int offset = 0;
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            float x = (2 * (i + 0.5) / (float)WIDTH - 1) * c_tan * WIDTH / (float)HEIGHT;
            float y = -(2 * (j + 0.5) / (float)HEIGHT - 1) * c_tan;

            glm::vec3 dir = glm::vec3(x, y, -1);
            dir = glm::normalize(dir);
            glm::vec3 color = World::cast_ray(camera_offset, dir);

            float max_color = std::max(color[0], std::max(color[1], color[2]));
            if(max_color > 1) color *= 1.f/max_color;

            pixels[offset] = floor(255 * color[0]);
            pixels[offset + 1] = floor(255 * color[1]);
            pixels[offset + 2] = floor(255 * color[2]);
            pixels[offset + 3] = 255;
            offset += 4;
        }
    }
}

bool World::scene_intersect(glm::vec3 orig, glm::vec3 dir,
                            glm::vec3 &t0_out, glm::vec3 &normal_out, Material &material_out)
{
    float sphere_dist = std::numeric_limits<float>::max();
    for (size_t i = 0; i < spheres.size(); i++)
    {
        float dist_i;
        if (spheres[i].intersection(orig, dir, dist_i) && dist_i < sphere_dist)
        {
            sphere_dist = dist_i;
            t0_out = orig + dir * dist_i;
            normal_out = glm::normalize((t0_out - spheres[i].center));
            material_out = spheres[i].material;
        }
    }
    return sphere_dist < 1000;
}

void World::add_sphere(glm::vec3 center, int radius, Material material)
{

    spheres.push_back(Sphere(center, radius, material));
}

void raytracer::World::add_light(glm::vec3 pos, float intensity)
{
    lights.push_back(Light(pos, intensity));
}
