#include "Graph.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace sf;

int main() {
  sf::Vector2i defaultDimensions(800, 800);
  sf::Vector2i dimensions = defaultDimensions;
  sf::RenderWindow window(sf::VideoMode(dimensions.x, dimensions.y),
                          "Mandelbrot", sf::Style::Default);

  std::string fileName = "ColorScheme_10.png";
  Graph mainGraph(dimensions, sf::Vector2<double>(-2, 2), Complex(0, 0),
                  fileName);

  bool needToUpdate = true;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == Keyboard::Escape)
        window.close();
      if (event.type == sf::Event::MouseButtonPressed &&
          ::Mouse::isButtonPressed(sf::Mouse::Left)) {
        mainGraph.setCameraOrigin(Mouse::getPosition(window));
        needToUpdate = true;
      }
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == Keyboard::A) {
        mainGraph.decZoom();
        needToUpdate = true;
      }
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == Keyboard::D) {
        mainGraph.incZoom();
        needToUpdate = true;
      }
      if (event.type == sf::Event::MouseWheelScrolled) {
        mainGraph.setCameraOrigin(Mouse::getPosition(window));
        if (event.mouseWheelScroll.delta > 0) {
          mainGraph.incZoom();
          needToUpdate = true;
        } else if (event.mouseWheelScroll.delta < 0) {
          mainGraph.decZoom();
          needToUpdate = true;
        }
      }
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == Keyboard::R) {
        mainGraph.resetView();
        needToUpdate = true;
      }
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == Keyboard::P) {
        mainGraph.printData();
      }
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == Keyboard::S) {
        if (mainGraph.saveImage())
          std::cout << "\nImage Saved" << std::endl;
      }
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == Keyboard::F) {
        if (dimensions == defaultDimensions) {
          dimensions.x = 1920;
          dimensions.y = 1080;
          window.create(sf::VideoMode(dimensions.x, dimensions.y), "Mandelbrot",
                        sf::Style::Fullscreen);
          mainGraph.create(dimensions, mainGraph.getxBounds(), fileName);
          needToUpdate = true;
        } else {
          dimensions = defaultDimensions;
          window.create(sf::VideoMode(dimensions.x, dimensions.y), "Mandelbrot",
                        sf::Style::Default);
          mainGraph.create(dimensions, mainGraph.getxBounds(), fileName);
          needToUpdate = true;
        }
      }
    }

    // Clear window
    window.clear(Color::White);

    if (needToUpdate) {
      mainGraph.update();
      needToUpdate = false;
    }

    // Draw to the window
    mainGraph.draw(window);
    window.display();
  }

  return 0;
}