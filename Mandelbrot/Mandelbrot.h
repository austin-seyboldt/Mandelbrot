#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Complex.h"
#include <iostream>
#include <string>
#include "ColorScheme.h"
#include <cmath>

class Mandelbrot
{
public:
	Mandelbrot(sf::Vector2i dimensions);
	Mandelbrot(sf::Vector2i dimensions, std::string &fileName);
	~Mandelbrot();
	void updateSet(sf::Vector2<double> xBounds, sf::Vector2<double> yBounds, double zoomFactor);
	void drawToImage(sf::Image&);
	unsigned getMaxIterations();
	void setMaxIterations(unsigned maxIterations);
private:
	sf::Uint8* pixels;
	sf::Vector2i dimensions;
	void setColor(sf::Uint8 *pixel, unsigned iterations);
	void setColor(sf::Uint8 *pixel, double magnitude, unsigned iterations, unsigned maxIterations);
	sf::Color getNormalizedColor(double magnitude, unsigned iterations, unsigned maxIterations);
	void calcMandel(sf::Uint8 * pixel, Complex num, unsigned maxIterations);
	void calcMandel(sf::Uint8 * point, Complex num, unsigned maxIterations, double xScale, double yScale);
	unsigned MAX_ITERATIONS = 100;
	ColorScheme scheme;
	double zoomFactor;
};