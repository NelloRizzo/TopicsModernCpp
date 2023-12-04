#include <iostream>
using namespace std;

class Rectangle {
	int width;
	int height;
public:
	Rectangle();
	Rectangle(int, int);
	void setDimensions(int, int);
	inline int area() const { return width * height; }
	inline int perimeter() const { return 2 * (width + height); }
};

//Rectangle::Rectangle() { width = 1; height = 1; }
//Rectangle::Rectangle() :width{ 1 }, height{ 1 } {  }
Rectangle::Rectangle() :Rectangle{ 1,1 } {  }
Rectangle::Rectangle(int w, int h) : width{ w }, height{ h } {}

void Rectangle::setDimensions(int w, int h) {
	width = w; height = h;
}

static void print(Rectangle* r) {
	cout << "Area: " << r->area() << ", Perimeter: " << r->perimeter() << endl;
	delete r;
}

int main()
{
	Rectangle r{};
	cout << "Area: " << r.area() << ", Perimeter: " << r.perimeter() << endl;
	Rectangle rect{ 15, 33 };
	cout << "Area: " << rect.area() << ", Perimeter: " << rect.perimeter() << endl;
	rect.setDimensions(10, 20);
	cout << "Area: " << rect.area() << ", Perimeter: " << rect.perimeter() << endl;

	Rectangle* r1 = new Rectangle{ 10, 40 };
	print(r1);
	cout << "Area: " << r1->area() << ", Perimeter: " << r1->perimeter() << endl;

	const Rectangle cr{ 1,3 };
	//cr.setDimension(1, 4); // ERROR: setDimension non è "const"
}