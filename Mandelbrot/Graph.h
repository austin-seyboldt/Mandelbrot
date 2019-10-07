#pragma once
#include "SFML/Graphics.hpp"
#include "Mandelbrot.h"
#include "Complex.h"
#include <iostream>
#include <string>
#include <iomanip>

class Graph
{
public:
	Graph(sf::Vector2i dimensions, sf::Vector2<double> xBounds, Complex origin);
	Graph(sf::Vector2i dimensions, sf::Vector2<double> xBounds, Complex origin, std::string &fileName);
	~Graph();
	void create(sf::Vector2i dimensions, sf::Vector2<double> xBounds);
	void create(sf::Vector2i dimensions, sf::Vector2<double> xBounds, std::string &fileName);
	void setCameraOrigin(Complex origin);
	void setCameraOrigin(sf::Vector2i mousePosition);
	void incZoom();
	void decZoom();
	void resetView();
	void update();
	void draw(sf::RenderWindow &window);
	void printData();
	bool saveImage();
	sf::Vector2<double> getxBounds();
private:
	Mandelbrot* mandel;
	double zoomSpeed;
	int zoomLvl;
	double zoomFactor;
	Complex origin;
	sf::Vector2i dimensions;
	sf::Vector2<double> xBounds;
	sf::Vector2<double> yBounds;
	sf::Image graphPlane;
	sf::Texture displayTexture;
	sf::Sprite displaySprite;
	const double DEFAULT_ZOOM_SPEED = .2;
	sf::Vector2<double> defaultXBounds;
	sf::Vector2<double> defaultYBounds;
};