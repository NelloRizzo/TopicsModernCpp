#pragma once
#include <iostream>
#include "Canvas.h"
using namespace std;

/// <summary>
/// A color into a bitmap.
/// </summary>
typedef struct {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
} Color;

/// <summary>
/// Literal operand to make Color from number (3 bytes RRGGBB).
/// </summary>
/// <param name="col">The number to convert into Color.</param>
/// <returns>The Color to set point into bitmap.</returns>
Color operator""_col(unsigned long long col); 
/// <summary>
/// A canvas that draw on a bitmap.
/// </summary>
class BitmapCanvas :public Canvas
{
private:
	Color* buffer;
	int width;
	int height;
	Color currentColor;
	Color backColor;

	constexpr int index(int x, int y) const { return y * width + x; }
public:
	// Inherited through Canvas
	int getWidth() const override { return width; }
	int getHeight() const override { return height; }
	void clear() override;
	void setPoint(int x, int y) override;
	void resetPoint(int x, int y) override;
	bool isOn(int x, int y) const override;

	BitmapCanvas(int width, int height) : BitmapCanvas(width, height, Color{ 255,255,255 }) {}
	BitmapCanvas(int width, int height, Color backColor)
		: width{ width }, height{ height }, backColor{ backColor }, buffer{ new Color[width * height] }
	{
		clear();
	}
	/// <summary>
	/// Set the current color of next points.
	/// </summary>
	/// <param name="color">The color.</param>
	void setCurrentColor(Color color) { currentColor = color; }
	/// <summary>
	/// Out the canvas to a bitmap on the stream.
	/// </summary>
	/// <param name="s">The stream to write to.</param>
	ostream& out(ostream& s);
};

