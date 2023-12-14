#pragma once
#include "Canvas.h"
#include "Point.h"
/// <summary>
/// Base class for all shapes.
/// </summary>
class Shape
{
private:
	/// <summary>
	/// The x-axis of boundary first corner.
	/// </summary>
	int x1;
	/// <summary>
	/// The x-axis of boundary second corner.
	/// </summary>
	int x2;
	/// <summary>
	/// The y-axis of boundary first corner.
	/// </summary>
	int y1;
	/// <summary>
	/// The y axis of boundary second corner.
	/// </summary>
	int y2;

	constexpr int min(int x, int y) const { return x < y ? x : y; }
	constexpr int max(int x, int y) const { return x > y ? x : y; }
public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="x1">The x-axis of boundary first corner.</param>
	/// <param name="y1">The y-axis of boundary first corner.</param>
	/// <param name="x2">The x-axis of boundary second corner.</param>
	/// <param name="y2">The y axis of boundary second corner.</param>
	Shape(int x1, int y1, int x2, int y2) :x1{ x1 }, x2{ x2 }, y1{ y1 }, y2{ y2 } {}
	/// <summary>
	/// Draw the shape in the canvas.
	/// </summary>
	/// <param name="canvas">The canvas to write on.</param>
	virtual void draw(Canvas& canvas) const = 0;
	/// <returns>Top left corner of shape's boundary</returns>
	inline Point topLeft() const { return Point{ min(x1,x2), min(y1,y2) }; }
	/// <returns>Top right corner of shape's boundary</returns>
	inline Point topRight() const { return Point{ max(x1,x2), min(y1,y2) }; }
	/// <returns>Bottom left corner of shape's boundary</returns>
	inline Point bottomLeft() const { return Point{ min(x1,x2), max(y1,y2) }; }
	/// <returns>Bottom right corner of shape's boundary</returns>
	inline Point bottomRight() const { return Point{ max(x1,x2), max(y1,y2) }; }
};

