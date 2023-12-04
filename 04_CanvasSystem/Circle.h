#pragma once
#include "Ellipse.h"

class Circle :public Ellipse
{
public:
	Circle(int cx, int cy, int radius) : Ellipse(cx, cy, radius, radius) {}
};

