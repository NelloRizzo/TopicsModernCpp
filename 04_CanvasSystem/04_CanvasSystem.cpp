#include <iostream>
#include <fstream>

#include "Canvas.h"
#include "BlackAndWhiteCanvas.h"
#include "Rectangle.h"
#include "Square.h"
#include "Ellipse.h"
#include "Circle.h"
#include "BitmapCanvas.h"

using namespace std;

static void print(const Canvas& canvas) {
	int w = canvas.getWidth();
	int h = canvas.getHeight();
	cout << "  ";
	for (int c = 0; c < w; ++c) cout << c % 10;
	cout << endl;
	for (int r = 0; r < h; ++r) {
		cout << r % 10 << ' ';
		for (int c = 0; c < w; ++c) {
			cout << (canvas.isOn(c, r) ? '.' : ' ');
		}
		cout << endl;
	}
}

static void makeGraphics(Canvas& canvas, int multiplier = 1) {
	Rectangle{ 5*multiplier, 10 * multiplier, 20 * multiplier, 20 * multiplier }.draw(canvas);
	Square{ 12 * multiplier, 12 * multiplier, 10 * multiplier }.draw(canvas);
	Ellipse{ 30 * multiplier, 7 * multiplier, 15 * multiplier, 5 * multiplier }.draw(canvas);
	Circle{ 30 * multiplier, 7 * multiplier, 5 * multiplier }.draw(canvas);
}

int main()
{
	BlackAndWhiteCanvas c{ 80, 23 };
	makeGraphics(c);
	print(c);
	BitmapCanvas bc{ 800, 230 };
	bc.setCurrentColor(0xcc00cc_col);
	makeGraphics(bc, 10);
	ofstream os("output.bmp", ios::binary);
	bc.out(os);
	os.close();
}