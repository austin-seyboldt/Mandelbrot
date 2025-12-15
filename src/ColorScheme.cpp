#include "ColorScheme.h"
#include <filesystem>

std::filesystem::path exeDir =
    std::filesystem::canonical("/proc/self/exe").parent_path();

std::string get_file_path(const std::string &fileName) {
  auto colorPath = exeDir / "assets/color_schemes" / fileName;
  return colorPath.string();
}

ColorScheme::ColorScheme() {
  sf::Image palette;
  if (palette.loadFromFile(get_file_path("Default_Hue.png"))) {
    sf::Vector2u size = palette.getSize();
    unsigned width = size.x;

    for (unsigned i = 0; i < width; i++) {
      scheme.push_back(palette.getPixel(i, 0));
    }
  }
  colorShift = 0;
}

ColorScheme::ColorScheme(const std::string &fileName) {
  sf::Image palette;
  if (palette.loadFromFile(get_file_path(fileName))) {
    sf::Vector2u size = palette.getSize();
    unsigned width = size.x;

    for (unsigned i = 0; i < width; i++) {
      scheme.push_back(palette.getPixel(i, 0));
    }
  }
  colorShift = 0;
}

bool ColorScheme::loadFromFile(const std::string &fileName) {
  bool success = false;
  sf::Image palette;
  if (palette.loadFromFile(get_file_path(fileName))) {
    success = true;
    sf::Vector2u size = palette.getSize();
    unsigned width = size.x;

    scheme.clear();
    for (unsigned i = 0; i < width; i++) {
      scheme.push_back(palette.getPixel(i, 0));
    }
  }
  return success;
}

sf::Color ColorScheme::getColor(float hue) {
  if (hue > 1)
    hue = 1;
  unsigned index = unsigned(1 + unsigned((hue + colorShift) * scheme.size()) %
                                    scheme.size());
  return scheme[index];
}

sf::Color ColorScheme::getBaseColor() { return scheme[0]; }

void ColorScheme::shiftColor(float shift) {
  if (shift < 1.0)
    colorShift = shift;
  else {
    colorShift = 0.;
  }
}
