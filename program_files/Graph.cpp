#include "pch.h"
#include "Graph.h"

Graph::Graph(sf::Vector2i dimensions, sf::Vector2<double> xBounds, Complex origin)
{
	mandel = new Mandelbrot(dimensions);
	this->dimensions = dimensions;
	zoomSpeed = DEFAULT_ZOOM_SPEED;
	zoomLvl = 1;
	zoomFactor = 1;
	float dimensionRatio = 1.0 * dimensions.y / dimensions.x;
	this->xBounds = xBounds;
	this->origin.real = origin.real;
	this->origin.imaginary = origin.imaginary;
	this->yBounds.x = origin.imaginary - (dimensionRatio * (xBounds.y - xBounds.x) / 2);
	this->yBounds.y = origin.imaginary + (dimensionRatio * (xBounds.y - xBounds.x) / 2);

	defaultXBounds = sf::Vector2<double>(-2,2);
	defaultYBounds = sf::Vector2<double>(-2*dimensionRatio, 2*dimensionRatio);

	/*
	std::cout << "Xbounds: " << xBounds.x << " " << xBounds.y << std::endl;
	std::cout << "Ybounds: " << yBounds.x << " " << yBounds.y << std::endl;
	std::cout << "Origin: " << origin.real << " + " << origin.imaginary << "i" << std::endl;
	*/
}

Graph::Graph(sf::Vector2i dimensions, sf::Vector2<double> xBounds, Complex origin, std::string &fileName)
{
	mandel = new Mandelbrot(dimensions, fileName);
	this->dimensions = dimensions;
	zoomSpeed = DEFAULT_ZOOM_SPEED;
	zoomLvl = 1;
	zoomFactor = 1;
	float dimensionRatio = 1.0 * dimensions.y / dimensions.x;
	this->xBounds = xBounds;
	this->origin.real = origin.real;
	this->origin.imaginary = origin.imaginary;
	this->yBounds.x = origin.imaginary - (dimensionRatio * (xBounds.y - xBounds.x) / 2);
	this->yBounds.y = origin.imaginary + (dimensionRatio * (xBounds.y - xBounds.x) / 2);

	defaultXBounds = sf::Vector2<double>(-2, 2);
	defaultYBounds = sf::Vector2<double>(-2 * dimensionRatio, 2 * dimensionRatio);

	/*
	std::cout << "Xbounds: " << xBounds.x << " " << xBounds.y << std::endl;
	std::cout << "Ybounds: " << yBounds.x << " " << yBounds.y << std::endl;
	std::cout << "Origin: " << origin.real << " + " << origin.imaginary << "i" << std::endl;
	*/
}

Graph::~Graph()
{
	delete mandel;
	mandel = nullptr;
}

void Graph::create(sf::Vector2i dimensions, sf::Vector2<double> xBounds) 
{
	delete mandel;
	mandel = new Mandelbrot(dimensions);
	this->dimensions = dimensions;
	float dimensionRatio = 1.0 * dimensions.y / dimensions.x;
	this->xBounds = xBounds;
	this->yBounds.x = origin.imaginary - (dimensionRatio * (xBounds.y - xBounds.x) / 2);
	this->yBounds.y = origin.imaginary + (dimensionRatio * (xBounds.y - xBounds.x) / 2);

	displaySprite.setTextureRect(sf::IntRect(0, 0, dimensions.x, dimensions.y));

}

void Graph::create(sf::Vector2i dimensions, sf::Vector2<double> xBounds, std::string &fileName)
{
	delete mandel;
	mandel = new Mandelbrot(dimensions, fileName);
	this->dimensions = dimensions;
	float dimensionRatio = 1.0 * dimensions.y / dimensions.x;
	this->xBounds = xBounds;
	this->yBounds.x = origin.imaginary - (dimensionRatio * (xBounds.y - xBounds.x) / 2);
	this->yBounds.y = origin.imaginary + (dimensionRatio * (xBounds.y - xBounds.x) / 2);

	displaySprite.setTextureRect(sf::IntRect(0, 0, dimensions.x, dimensions.y));
}

void Graph::setCameraOrigin(Complex origin)
{
	this->origin = origin;
}

void Graph::setCameraOrigin(sf::Vector2i mousePosition)
{
	origin.real = xBounds.x + (((xBounds.y - xBounds.x) / dimensions.x) * mousePosition.x);
	origin.imaginary = yBounds.x + (((yBounds.y - yBounds.x) / dimensions.y) * mousePosition.y);
	double xChange = abs(xBounds.y - xBounds.x) / 2;
	double yChange = abs(yBounds.y - yBounds.x) / 2;
	xBounds.x = origin.real - xChange;
	xBounds.y = origin.real + xChange;
	yBounds.x = origin.imaginary - yChange;
	yBounds.y = origin.imaginary + yChange;
}

// Find a better way of representing zoom!!
void Graph::incZoom()
{
	++zoomLvl;
	zoomFactor += zoomLvl * zoomSpeed;
	double xChange = abs((xBounds.y - xBounds.x) / 2 / zoomFactor);
	double yChange = abs((yBounds.y - yBounds.x) / 2 / zoomFactor);
	xBounds.x = origin.real - xChange;
	xBounds.y = origin.real + xChange;
	yBounds.x = origin.imaginary - yChange;
	yBounds.y = origin.imaginary + yChange;
}

// Fix this shit too
void Graph::decZoom()
{
	--zoomLvl;
	zoomFactor -= zoomLvl * zoomSpeed;
	double xChange = abs((xBounds.y - xBounds.x) / 2 * zoomFactor);
	double yChange = abs((yBounds.y - yBounds.x) / 2 * zoomFactor);
	xBounds.x = origin.real - xChange;
	xBounds.y = origin.real + xChange;
	yBounds.x = origin.imaginary - yChange;
	yBounds.y = origin.imaginary + yChange;
}

void Graph::resetView()
{
	zoomSpeed = DEFAULT_ZOOM_SPEED;
	zoomLvl = 1;
	zoomFactor = 1;
	origin.real = 0;
	origin.imaginary = 0;
	xBounds = defaultXBounds;
	double dimensionRatio = 1.0 * dimensions.y / dimensions.x;
	yBounds.x = origin.imaginary - (dimensionRatio * (xBounds.y - xBounds.x) / 2);
	yBounds.y = origin.imaginary + (dimensionRatio * (xBounds.y - xBounds.x) / 2);
}

void Graph::draw(sf::RenderWindow & window)
{
	mandel->drawToImage(graphPlane);
	displayTexture.loadFromImage(graphPlane);
	displaySprite.setTexture(displayTexture);
	window.draw(displaySprite);
}

void Graph::update()
{
	mandel->updateSet(xBounds, yBounds, zoomFactor);
}

void Graph::printData()
{
	std::cout << std::fixed << std::setprecision(16) << std::showpoint << std::endl;
	std::cout << "\nOrigin: " << origin.real << " + " << origin.imaginary << "i" << std::endl;
	std::cout << "xBounds: " << xBounds.x << " " << xBounds.y << std::endl;
	std::cout << "yBounds: " << yBounds.x << "i " << yBounds.y << "i" << std::endl;
	std::cout << "ZoomFactor: " << zoomFactor << std::endl;
	// std::cout << "Magnification: " << std::pow(2, zoomFactor) << std::endl;
	std::cout << "Max iterations: " << mandel->getMaxIterations() * zoomFactor << std::endl;
}

bool Graph::saveImage()
{
	std::string fileName = "Mandelbrot_x";
	fileName = fileName + std::to_string(xBounds.x) + "_" + std::to_string(xBounds.y) + 
		"o" + std::to_string(origin.real) + "_" + std::to_string(origin.imaginary) + ".png";
	return graphPlane.saveToFile(fileName);
}

sf::Vector2<double> Graph::getxBounds()
{
	return xBounds;
}