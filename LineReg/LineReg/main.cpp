#include "points.hpp"
#include "regression.hpp"
#include <iostream>

int main() {

	Points points;
	points.generate_random_points(10, 50, -50, 50, -50);		// generates n number of points between MAX X and MIN X and MAX Y and MIN Y

	std::cout << points;

	std::cout << "Equation of regression line equals: " << guess_y(10, points) << std::endl;		// Y = mx + b | m = slope | b = y intercept

	return 0;
}