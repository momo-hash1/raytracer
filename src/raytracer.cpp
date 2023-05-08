#include "headers/constants.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "../included/glm/vec3.hpp"
#include <limits>
#include <algorithm>
#include <iostream>
#include "headers/raytracer.h"
#include "headers/material.h"


float norm(glm::vec3 theta)
{
    return sqrtf(theta.x * theta.x + theta.y * theta.y + theta.z * theta.z);
}

using namespace raytracer;

raytracer::World::World(Screen& screen) : m_screen{ screen }
{
}

glm::vec3 World::cast_ray(glm::vec3 orig, glm::vec3 dir, size_t depth = 0)
{
    glm::vec3 t0, normal;
    Material material;
    float diffuse_light = 0;
    float specular = 0;
    if (depth > 4 || !scene_intersect(orig, dir, t0, normal, material))
    {
        return glm::vec3(0, 0, 0);
    }

    glm::vec3 reflect_dir = glm::normalize(glm::reflect(dir, normal));
    glm::vec3 reflect_orig = glm::dot(reflect_dir, normal) < 0 ? t0 - normal * 1e-3f : t0 + normal * 1e-3f;
    glm::vec3 reflect_color = cast_ray(reflect_orig, reflect_dir, depth + 1);

    glm::vec3 refract_dir = glm::normalize(glm::refract(dir, normal, 1.333f));
    glm::vec3 refract_orig = glm::dot(refract_dir, normal) < 0 ? t0 - normal * 1e-3f : t0 + normal * 1e-3f;
    glm::vec3 refract_color = cast_ray(refract_orig, refract_dir, depth + 1);

    for (size_t i = 0; i < lights.size(); i++)
    {
        glm::vec3 theta = lights[i].position - t0;
        glm::vec3 light_dir = glm::normalize(theta);

        float light_distance = norm(theta);
        glm::vec3 shadow_orig = glm::dot(light_dir, normal) < 0 ? t0 - normal * 1e-3f : t0 + normal * 1e-3f;

        glm::vec3 shadow_t0, shadow_n;
        Material tmpmat;

        if (scene_intersect(shadow_orig, light_dir, shadow_t0,
                            shadow_n, tmpmat) &&
            norm(shadow_t0 - shadow_orig) < light_distance)
        {
            continue;
        }

        diffuse_light += lights[i].intensity * std::max(0.f, glm::dot(light_dir, normal));
        specular += powf(std::max(0.f, glm::dot(glm::reflect(light_dir, normal), dir)), material.specular) * lights[i].intensity;
    }

    return material.color * diffuse_light + 0.1f * glm::vec3(1.f, 1.f, 1.f) * specular +
           reflect_color * material.reflect_ratio + refract_color * material.refract;
}

void World::render()
{
    float fov = 1.05;
    float c_tan = tan(fov / 2.);
    const int width{ m_screen.getSize()[0] };
    const int height{ m_screen.getSize()[1] };
    #pragma omp parallel for

    for (int i = 0; i < m_screen.getActualSize(); i += COLOR_STEP)
    {
        const int y_pos = (i / COLOR_STEP) / width;
        const int x_pos = (i / COLOR_STEP) - (width * y_pos);

        float x = (2 * (x_pos + 0.5) / (float)width - 1) * c_tan * width / (float)height;
        float y = -(2 * (y_pos + 0.5) / (float)height - 1) * c_tan;

        glm::vec3 dir = glm::vec3(x, y, -1);
        dir = glm::normalize(dir);

        glm::vec3 color_pixel = World::cast_ray(glm::vec3(0, 0, 0), dir);

        m_screen.setPixel(i, color_pixel);
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
