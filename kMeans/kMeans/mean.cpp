#include "mean.hpp"

double Regression::mean(std::list<double> set) {
	double answer = 0;
	for (double i : set) {
		answer += i;
	}
	answer /= set.size();
	return answer;
}