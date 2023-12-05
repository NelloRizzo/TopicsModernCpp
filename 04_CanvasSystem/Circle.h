#pragma once
#include "Ellipse.h"
/// <summary>
/// A circle.
/// </summary>
class Circle :public Ellipse
{
public:
	Circle(int cx, int cy, int radius) : Ellipse(cx, cy, radius, radius) {}
};

