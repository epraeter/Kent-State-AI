#ifndef AI_REGRESSION
#define AI_REGRESSION

#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include "points.hpp"

double mean(std::list<double> set) {
	double answer = 0;
	for (double i : set) {
		answer += i;
	}
	answer /= set.size();
	return answer;
};

double find_slope(const Points& points) {
	double numerator = 0;
	double denominator = 0;
	std::list<double> x;
	std::list<double> y;
	for (int i = 0; i < points.get_size(); i++) {
		x.push_back(points[i].x);
		y.push_back(points[i].y);
	}
	double x_mean = mean(x);	// gets x mean
	double y_mean = mean(y);	// gets y mean

	for (int i = 0; i < points.get_size(); i++) {
		numerator += (points[i].x - x_mean) * (points[i].y - y_mean);
		denominator += pow((points[i].x - x_mean), 2);
		// can add numerator / denominator here to see slope after each point
	}
	//std::cout << numerator << "\n";		
	//std::cout << denominator << "\n";	

	return numerator / denominator;	// final slope
};

double find_y_intercept(const Points& points) {
	std::list<double> x;
	std::list<double> y;
	for (int i = 0; i < points.get_size(); i++) {
		x.push_back(points[i].x);
		y.push_back(points[i].y);
	}
	double x_mean = mean(x);
	double y_mean = mean(y);

	double slope = find_slope(points);

	return (y_mean - (slope * x_mean)); // final y intercept
};

double guess_y(double x, const Points& points) {
	double slope = find_slope(points);
	double y_int = find_y_intercept(points);
	std::cout << "Slope is: " << slope << '\n';
	std::cout << "Y intercept is: " << y_int << '\n';
	return ((slope * x) + y_int);					// returns  Y = slope * x + y intercept  == equation fo the regression line
};

#endif 