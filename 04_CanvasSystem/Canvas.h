#pragma once

/// <summary>
/// A canvas that provides primitives to graphics.
/// </summary>
class Canvas
{
public:
	/// <summary>
	/// Virtual destructor to guarantee destruction of subclasses.
	/// </summary>
	virtual ~Canvas() {}
	/// <returns>The width of canvas.</returns>
	virtual int getWidth() const = 0;
	/// <returns>The height of canvas.</returns>
	virtual int getHeight() const = 0;
	/// <summary>
	/// Clear the canvas.
	/// </summary>
	virtual void clear();
	/// <summary>
	/// Set a point into canvas.
	/// </summary>
	/// <param name="x">The x-axis.</param>
	/// <param name="y">The y-axis.</param>
	virtual void setPoint(int x, int y) = 0;
	/// <summary>
	/// Reset a point into canvas.
	/// </summary>
	/// <param name="x">The x-axis.</param>
	/// <param name="y">The y-axis.</param>
	virtual void resetPoint(int x, int y) = 0;
	/// <summary>
	/// Check if a point is setted.
	/// </summary>
	/// <param name="x">The x-axis.</param>
	/// <param name="y">The y-axis.</param>
	/// <returns>A boolean that indicates if the point is setted.</returns>
	virtual bool isOn(int x, int y) const = 0;
	/// <summary>
	/// Draw a line into canvas.
	/// </summary>
	/// <param name="x1">The x-axis of first point.</param>
	/// <param name="y1">The y-axis of first point.</param>
	/// <param name="x2">The x-axis of second point.</param>
	/// <param name="y2">The y-axis of second point.</param>
	void line(int x1, int y1, int x2, int y2);
};

