#pragma once
#include "Canvas.h"
class BlackAndWhiteCanvas :public Canvas
{
private:
	bool* grid;
	int width;
	int height;

	inline bool isPointInGrid(int x, int y) const { return x > -1 && x < width && y > -1 && y < height; }
	inline void setPoint(int x, int y, bool on) { if (isPointInGrid(x, y)) grid[index(x, y)] = on; }
	constexpr int index(int x, int y) const { return y * width + x; }
public:
	// Inherited through Canvas
	inline void setPoint(int x, int y) override { setPoint(x, y, true); }
	void resetPoint(int x, int y) override { setPoint(x, y, false); }
	inline bool isOn(int x, int y)const override { return isPointInGrid(x, y) ? grid[index(x, y)] : false; }
	inline int getWidth() const override { return width; }
	inline int getHeight() const override { return height; }

	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="width">The width of the canvas.</param>
	/// <param name="height">The height of the canvas.</param>
	BlackAndWhiteCanvas(int width, int height) :width{ width }, height{ height }, grid{ new bool[static_cast<long long>(height) * width] } { clear(); }
	/// <summary>
	/// Destroy the grid.
	/// </summary>
	~BlackAndWhiteCanvas() { delete[] grid; }
};

