#include "Canvas.h"

constexpr int min(int x, int y) { return x < y ? x : y; }
constexpr int max(int x, int y) { return x > y ? x : y; }

void Canvas::clear()
{
	int h = getHeight();
	int w = getWidth();
	for (int r = 0; r < h; ++r)for (int c = 0; c < w; ++c) resetPoint(c, r);
}

void Canvas::line(int x1, int y1, int x2, int y2)
{
	int minx = min(x1, x2);
	int maxx = max(x1, x2);
	int miny = min(y1, y2);
	int maxy = max(y1, y2);

	if (x1 == x2) {
		for (int y = miny; y <= maxy; ++y) setPoint(x1, y);
	}
	else {
		float m = 1.0f * (y1 - y2) / (x1 - x2);
		float q = 1.0f * (x1 * y2 - x2 * y1) / (x1 - x2);
		for (float x = minx; x <= maxx; x += .1f) {
			setPoint(static_cast<int>(x), static_cast<int>(m * x + q));
		}
	}
}
