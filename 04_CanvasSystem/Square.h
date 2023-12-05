#pragma once
#include "Rectangle.h"
/// <summary>
/// A square.
/// </summary>
class Square:public Rectangle
{
public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="x1">The x-axis of boundary top left corner.</param>
	/// <param name="y1">The y-axis of boundary top left corner.</param>
	/// <param name="side"></param>
	Square(int x1, int y1, int side) :Rectangle(x1, y1, x1 + side, y1 + side) {}
};

