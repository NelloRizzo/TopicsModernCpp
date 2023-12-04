#include <iostream>

#include "MyClass.h"

static MyClass factory(string name) {
	cout << "MyClass::factory call ";
	return MyClass(name);
}


int main()
{
	cout << "Default constructor: ";
	MyClass m1;
	cout << "Constructor: ";
	MyClass m2("m2");
	cout << "Copy from " << m2 << ": ";
	{
		MyClass m3 = m2;
		cout << "Assignment from " << m2 << ": ";
		cout << "After copy: " << (m1 = m2) << endl;
	}
	cout << "m2 = " << m2.getName() << endl;
	cout << "Move from rvalue ";
	MyClass m4;
	m4 = factory("m4");
	MyClass m5 = std::move(MyClass("m5"));
}