#pragma once
#include <math.h>
#include "Shape.h"
#include "Canvas.h"
/// <summary>
/// An ellipse.
/// </summary>
class Ellipse :public Shape
{
private:
	int cx;
	int cy;
	int xradius;
	int yradius;
public:
	Ellipse(int cx, int cy, int xradius, int yradius) :Shape(cx - xradius, cy - yradius, cx + xradius, cy + yradius),
		cx{ cx }, cy{ cy }, xradius{ xradius }, yradius{ yradius }
	{}
	void draw(Canvas& canvas) const override {
		int xs = cx + xradius;
		int ys = cy;
		for (float a = 0; a < 6.3f; a += .1f) {
			int x = cx + static_cast<int>(cos(a) * xradius);
			int y = cy + static_cast<int>(sin(a) * yradius);
			canvas.line(xs, ys, x, y);
			xs = x;
			ys = y;
		}
	}
};

