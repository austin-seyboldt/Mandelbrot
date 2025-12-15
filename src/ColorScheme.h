#pragma once
#include <string>
#include "SFML/Graphics.hpp"

class ColorScheme
{
public:
	ColorScheme();
	ColorScheme(const std::string &fileName);
	bool loadFromFile(const std::string &fileName);
	sf::Color getColor(float hue);
	sf::Color getBaseColor();
	void shiftColor(float shift);
private:
	std::vector<sf::Color> scheme;
	float colorShift;
};