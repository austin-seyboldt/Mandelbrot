#include "Mandelbrot.h"
#include <iostream>

Mandelbrot::Mandelbrot(sf::Vector2i dimensions) {
  this->dimensions = dimensions;
  pixels = new sf::Uint8[dimensions.x * dimensions.y * 4];
  if (scheme.loadFromFile("hue.png"))
    std::cout << "Color scheme loaded" << std::endl;
  zoomFactor = 0;
}

Mandelbrot::Mandelbrot(sf::Vector2i dimensions, std::string &fileName)
    : scheme(fileName) {
  this->dimensions = dimensions;
  pixels = new sf::Uint8[dimensions.x * dimensions.y * 4];
  zoomFactor = 0;
}

Mandelbrot::~Mandelbrot() {
  delete[] pixels;
  pixels = nullptr;
}

void Mandelbrot::updateSet(sf::Vector2<double> xBounds,
                           sf::Vector2<double> yBounds, double zoomFactor) {
  std::cout << "Updating Mandelbrot Set..." << std::endl;
  std::cout << "X Bounds: " << xBounds.x << " to " << xBounds.y << std::endl;
  std::cout << "Y Bounds: " << yBounds.x << " to " << yBounds.y << std::endl;
  std::cout << "Dimensions: " << dimensions.x << " x " << dimensions.y
            << std::endl;
  double xYminusXmin = std::abs(xBounds.y - xBounds.x);
  std::cout << "X Range: " << xYminusXmin << std::endl;
  double xScale = static_cast<double>(std::abs(xBounds.y - xBounds.x)) /
                  static_cast<double>(dimensions.x);
  double yScale = static_cast<double>(std::abs(yBounds.y - yBounds.x)) /
                  static_cast<double>(dimensions.y);
  std::cout << "X Scale: " << xScale << ", Y Scale: " << yScale << std::endl;

  // Code for shifting colors with zoom - update graph zoom first
  /*
  if (zoomFactor != this->zoomFactor)
  {
          if (zoomFactor > 1.)
          {
                  this->zoomFactor = zoomFactor;
                  scheme.shiftColor(1. / (zoomFactor));
          }
          else
                  scheme.shiftColor(0);
  }
  */

  for (int y = 0; y < dimensions.y; y++) {
    for (int x = 0; x < dimensions.x; x++) {
      // std::cout << "Complex: " << xBounds.x + xScale * x << " + "
      //           << yBounds.x + yScale * y << "i" << std::endl;
      calcMandel((pixels + (y * dimensions.x * 4) + (x * 4)),
                 Complex(xBounds.x + xScale * x, yBounds.x + yScale * y),
                 MAX_ITERATIONS * zoomFactor);
      // calcMandel((pixels + (y * dimensions.x * 4) + (x * 4)),
      // Complex(xBounds.x + xScale * x, yBounds.x + yScale * y),
      // MAX_ITERATIONS*zoomFactor, xScale/2, yScale/2);
    }
  }
}

void Mandelbrot::calcMandel(sf::Uint8 *point, Complex num,
                            unsigned maxIterations) {
  unsigned iterations = 0;
  Complex result = num;
  Complex constant = num;
  double mag;
  while (iterations < maxIterations) {
    result = (result * result) + constant;
    mag = result.getMagnitude();
    if (mag > 2) {
      setColor(point, mag, iterations, maxIterations);
      break;
    }
    ++iterations;
  }
  // The result is inside the set, color it black
  if (iterations == maxIterations) {
    *(point) = scheme.getBaseColor().r;
    *(point + 1) = scheme.getBaseColor().g;
    *(point + 2) = scheme.getBaseColor().b;
    *(point + 3) = scheme.getBaseColor().a;
  }
}

void Mandelbrot::calcMandel(sf::Uint8 *point, Complex num,
                            unsigned maxIterations, double xScale,
                            double yScale) {
  float hue = 0;
  unsigned totalIterations = 0;
  Complex result;
  Complex c;
  Complex cArray[9] = {num,
                       Complex(num.real + xScale, num.imaginary),
                       Complex(num.real - xScale, num.imaginary),
                       Complex(num.real, num.imaginary + yScale),
                       Complex(num.real, num.imaginary - yScale),
                       Complex(num.real + xScale, num.imaginary + yScale),
                       Complex(num.real + xScale, num.imaginary - yScale),
                       Complex(num.real - xScale, num.imaginary - yScale),
                       Complex(num.real - xScale, num.imaginary + yScale)};
  sf::Color colorArray[9];

  for (int i = 0; i < 5; i++) {
    result = cArray[i];
    c = cArray[i];
    unsigned iterations = 0;
    while (iterations < maxIterations) {
      ++iterations;
      ++totalIterations;
      result = (result * result) + c;
      // The result isn't in the set, so color the pixels
      double mag = result.getMagnitude();
      if (mag > 2) {
        colorArray[i] = getNormalizedColor(mag, iterations, maxIterations);
        break;
      }
    }
  }
  if (totalIterations / 5 == maxIterations) {
    *(point) = scheme.getBaseColor().r;
    *(point + 1) = scheme.getBaseColor().g;
    *(point + 2) = scheme.getBaseColor().b;
    *(point + 3) = scheme.getBaseColor().a;
    return;
  }

  unsigned red = 0;
  unsigned green = 0;
  unsigned blue = 0;
  unsigned alpha = 0;

  for (int i = 0; i < 9; i++) {
    red = red + (colorArray[i].r * colorArray[i].r);
    green = green + (colorArray[i].g * colorArray[i].g);
    blue = blue + (colorArray[i].b * colorArray[i].b);
    alpha = alpha + (colorArray[i].a * colorArray[i].a);
  }

  red = red / 9;
  green = green / 9;
  blue = blue / 9;
  alpha = alpha / 9;

  *(point) = std::sqrt(red);
  *(point + 1) = std::sqrt(green);
  *(point + 2) = std::sqrt(blue);
  *(point + 3) = std::sqrt(alpha);
}

void Mandelbrot::setColor(sf::Uint8 *pixel, unsigned iterations) {
  unsigned hue = iterations % 4;

  switch (hue) {
  case 1:
    *(pixel) = 66;
    *(pixel + 1) = 173;
    *(pixel + 2) = 244;
    *(pixel + 3) = 255;
    break;
  case 2:
    *(pixel) = 66;
    *(pixel + 1) = 244;
    *(pixel + 2) = 217;
    *(pixel + 3) = 255;
    break;
  case 3:
    *(pixel) = 158;
    *(pixel + 1) = 244;
    *(pixel + 2) = 66;
    *(pixel + 3) = 255;
    break;
  case 4:
    *(pixel) = 223;
    *(pixel + 1) = 244;
    *(pixel + 2) = 66;
    *(pixel + 3) = 255;
    break;
  case 5:
    *(pixel) = 122;
    *(pixel + 1) = 99;
    *(pixel + 2) = 255;
    *(pixel + 3) = 255;
    break;
  case 6:
    *(pixel) = 122;
    *(pixel + 1) = 255;
    *(pixel + 2) = 206;
    *(pixel + 3) = 255;
    break;
  default:
    *(pixel) = 146;
    *(pixel + 1) = 66;
    *(pixel + 2) = 244;
    *(pixel + 3) = 255;
  }
}

void Mandelbrot::setColor(sf::Uint8 *pixel, double magnitude,
                          unsigned iterations, unsigned maxIterations) {
  // float hue = (double)iterations / maxIterations;
  // std::cout << "Iterations: " << iterations << ", Magnitude: " << magnitude
  //           << std::endl;
  float hue =
      (iterations - std::log2(std::log2(magnitude)) + 4.0) / maxIterations;

  *(pixel) = scheme.getColor(hue).r;
  *(pixel + 1) = scheme.getColor(hue).g;
  *(pixel + 2) = scheme.getColor(hue).b;
  *(pixel + 3) = 255;
}

sf::Color Mandelbrot::getNormalizedColor(double magnitude, unsigned iterations,
                                         unsigned maxIterations) {
  float hue =
      (iterations - std::log2(std::log2(magnitude)) + 4.0) / maxIterations;
  return scheme.getColor(hue);
}

void Mandelbrot::drawToImage(sf::Image &image) {
  image.create(dimensions.x, dimensions.y, &pixels[0]);
}

unsigned Mandelbrot::getMaxIterations() { return MAX_ITERATIONS; }

void Mandelbrot::setMaxIterations(unsigned max) { MAX_ITERATIONS = max; }