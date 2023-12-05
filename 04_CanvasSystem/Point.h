#pragma once
#include <math.h>
/// <summary>
/// A 2D point.
/// </summary>
struct Point
{
	int x;
	int y;

	Point(int x, int y) : x{ x }, y{ y } {}

	void moveTo(int x, int y) { this->x = x; this->y = y; }
	void moveBy(int dx, int dy) { x += dx; x += dy; }

	float dist(Point p) const {
		int dx = x - p.x;
		int dy = y - p.y;
		return static_cast<float>(sqrt(dx * dx + dy * dy));
	}
};

