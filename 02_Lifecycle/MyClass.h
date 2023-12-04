#pragma once

#include <iostream>
#include <string>
using namespace std;

class MyClass
{
private:
	string* name;
public:
	inline string getName() const { return *name; }

	MyClass() :MyClass("Anonymous") {
		cout << "Default constructor delegating MyClass(string) producing " << *this << endl;
	}
	MyClass(const string& name) : name{ new string(name) } {
		cout << "Constructor of " << *this << endl;
	}
	MyClass(const MyClass& other) : name{ new string(*other.name) } {
		cout << "Copy constructor from " << other << endl;
	}
	MyClass& operator=(const MyClass& other) {
		cout << "Copy assignment from " << other << endl;
		delete name;
		name = new string(*other.name);
		return *this;
	}
	MyClass(MyClass&& other) noexcept :name{ other.name } {
		other.name = nullptr;
		cout << "Move constructor move inner pointer of r-value, constructing " << *this << "\n\tnow other.name is nullptr" << endl;
	}
	MyClass& operator=(MyClass&& other) noexcept {
		delete name;
		name = other.name;
		other.name = nullptr;
		cout << "Move assignment and delete inner pointer of r-value, constructing " << *this << "\n\tnow other.name is nullptr" << endl;
		return *this;
	}
	~MyClass() {
		cout << "Destructor of MyClass. Now name will be deleted" << endl;
		delete name;
	}
	friend ostream& operator << (ostream& s, const MyClass& c) {
		return s << "MyClass(" << *c.name << ')';
	}
};

