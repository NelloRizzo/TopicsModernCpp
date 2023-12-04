#include <iostream>
#include "Ratio.h"
using namespace std;
using namespace ratio;
int main()
{
	cout << "gcf(10, 30) = " << Ratio::gcf(10, 30) << endl;
	Ratio r{ "-10/30" };
	Ratio a = r;
	a = r;

	a = 1.0 / -2;
	cout << "a = " << a << endl;

	float f = r;
	cout << r << " as float = " << f << endl;

	//string s = r; // implicit cast not allowed
	string s = static_cast<string>(r);
	//string s = (string)(r); // or also dynamic cast...
	cout << r << " as string = " << r << endl;

	cout << r << " + " << Ratio{ "1/3" } << " = " << r + Ratio{ "1/3" } << endl;
	cout << r << " - " << Ratio{ "1/3" } << " = " << r - Ratio{ "1/3" } << endl;
	cout << r << " * " << Ratio{ "1/3" } << " = " << r * Ratio{ "1/3" } << endl;
	cout << r << " / " << Ratio{ "1/3" } << " = " << r / Ratio{ "1/3" } << endl;
}