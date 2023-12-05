#pragma once
#include "Canvas.h"
#include "Shape.h"
/// <summary>
/// A rectangle.
/// </summary>
class Rectangle :public Shape
{
public:
	/// <summary>
    /// Constructor.
    /// </summary>
    /// <param name="x1">The x-axis of boundary first corner.</param>
    /// <param name="y1">The y-axis of boundary first corner.</param>
    /// <param name="x2">The x-axis of boundary second corner.</param>
    /// <param name="y2">The y axis of boundary second corner.</param>
	Rectangle(int x1, int y1, int x2, int y2) :Shape(x1, y1, x2, y2) {}

	void draw(Canvas& canvas) const override {
		Point tl = topLeft();
		Point tr = topRight();
		Point bl = bottomLeft();
		Point br = bottomRight();
		// draw top side
		canvas.line(tl.x, tl.y, tr.x, tr.y);
		// draw bottom side
		canvas.line(bl.x, bl.y, br.x, br.y);
		// draw left side
		canvas.line(tl.x, tl.y, bl.x, bl.y);
		// draw right side
		canvas.line(tr.x, tr.y, br.x, br.y);
	}
};

