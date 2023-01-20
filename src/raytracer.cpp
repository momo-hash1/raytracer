#include "headers/raytracer.h"
#include "headers/constants.h"
#include "headers/raytracer.h"
#include <algorithm>
#include <cmath>
#include <iostream>

void raytracer::render(sf::Uint8 *pixels)
{
    for (int j = 4; j < HEIGHT * 4; j+=4)
    {
        for (int i = 4; i < WIDTH * 4; i+=4)
        {
            double x = i-4;
            double y = j-4;
            int res_pos = x + y * WIDTH;
            
            pixels[res_pos] = floor(255 * std::max(0.d, std::min(1.d, y / HEIGHT)));
            pixels[res_pos + 1] = floor(255 * std::max(0.d, std::min(1.d, (x / WIDTH))));
            pixels[res_pos + 2] = 0;
            pixels[res_pos + 3] = 255;
        }

    }
}