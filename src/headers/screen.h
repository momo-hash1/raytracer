#pragma once
#include <array>
#include "../included/glm/vec3.hpp"
#include <string>
#include <vector>

class Screen
{
	using pixelType = int;
private:
	std::vector<pixelType> m_pixel_array;
	int m_width;
	int m_height;

public:
	Screen(int width, int height);
	void setPixel(int x, int y, glm::vec3 color);
	void setPixel(int pixel_pos, glm::vec3 color);
	void resize(int width, int height);
	std::array<int, 2> getSize();
    const std::vector<pixelType>& getPixelArray();
	void dumpToFile(std::string name);

	int getActualSize(int width, int height);
	int getActualSize();
};

