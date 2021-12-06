#ifndef AI_POINTS
#define AI_POINTS

#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Point {
	double x;
	double y;

	Point(double ix, double iy) { x = ix; y = iy; };
	bool operator==(const Point&);
};

class Points {
private:
	std::vector<Point> pts;
	int size; // number of points in pts

public:
	Points() { size = 0; };

	void   generate_random_points(int, double maxX, double minX, double maxY, double minY);
	int    check(const Point&);	//check for point in pts
	int    get_size()const { return size; };
	Point& operator[]            (int);

	const Point& operator[]      (int)const;
	friend std::ostream& operator<<(std::ostream&, const Points&);

};

#endif