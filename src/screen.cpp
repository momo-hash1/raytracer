#include "headers/screen.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "headers/constants.h"


Screen::Screen(int width, int height) : 
								m_width{ width }
								, m_height{ height }
								, m_pixel_array{}
{
	m_pixel_array.resize(getActualSize(width, height));
}

void Screen::setPixel(int x, int y, glm::vec3 color)
{
	const int actual_y{ y * m_width * COLOR_STEP };
	const int actual_pos{ (actual_y + m_width * y) * COLOR_STEP };

	setPixel(actual_pos, color);
}

void Screen::setPixel(int pixel_pos, glm::vec3 color)
{
	float max_color = std::max(color[0], std::max(color[1], color[2]));
	if (max_color > 1)
		color *= 1.f / max_color;

	m_pixel_array[pixel_pos] = floor(255 * color[0]);
	m_pixel_array[pixel_pos + 1] = floor(255 * color[1]);
	m_pixel_array[pixel_pos + 2] = floor(255 * color[2]);
}

void Screen::resize(int width, int height)
{
	m_width = width;
	m_height = height;

	m_pixel_array.resize(getActualSize());
}

std::array<int, 2> Screen::getSize()
{
	return std::array<int, 2>{m_width, m_height};
}

const std::vector<Screen::pixelType>& Screen::getPixelArray()
{
	return m_pixel_array;
}

void Screen::dumpToFile(std::string name)
{
	std::ofstream ofs;

	std::string filename{ "./" + name + ".ppm" };

	ofs.open(filename, std::ios::out | std::ios::binary);
	const std::array<int, 2> size{ getSize() };
	ofs << "P6\n" << size[0] << " " << size[1] << "\n255\n";
	for (size_t i = 0; i < getActualSize(); ++i)
	{
		ofs << static_cast<char>(m_pixel_array[i]);
	}
	ofs.close();
}

int Screen::getActualSize(int width, int height)
{
	return width * height * COLOR_STEP;
}

int Screen::getActualSize()
{
	return getActualSize(m_width, m_height);
}
