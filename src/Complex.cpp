#include "Complex.h"

Complex::Complex() {
  real = 0.;
  imaginary = 0.;
}

Complex::Complex(double r, double i) {
  real = r;
  imaginary = i;
}

Complex Complex::operator*(Complex &rhs) {
  return Complex(real * rhs.real + imaginary * rhs.imaginary * -1.,
                 imaginary * rhs.real + real * rhs.imaginary);
}

Complex Complex::operator+(Complex &rhs) {
  return Complex(real + rhs.real, imaginary + rhs.imaginary);
}

double Complex::getMagnitude() {
  return std::sqrt(real * real + imaginary * imaginary);
}