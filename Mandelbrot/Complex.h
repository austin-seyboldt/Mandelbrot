#pragma once
#include <cmath>

class Complex
{
public:
	Complex(double, double);
	Complex();
	Complex operator*(Complex & rhs);	// Overload multiplication operator
	Complex operator+(Complex & rhs);	// Overload plus operator
	double getMagnitude();
	double real;
	double imaginary;
};