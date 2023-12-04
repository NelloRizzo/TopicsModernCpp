#pragma once
#include <iostream>
#include "Canvas.h"
using namespace std;

typedef struct {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
} Color;

Color operator""_col(unsigned long long col); 

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
	void setCurrentColor(Color color) { currentColor = color; }

	ostream& out(ostream& s);
};

