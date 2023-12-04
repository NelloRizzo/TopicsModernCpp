#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Base {
protected:
	int value;
public:
	Base() = default;
	Base(int value) : value{ value } {}

	string out() const {
		stringstream ss;
		ss << "Base(" << value << ")";
		return ss.str();
	}
	virtual string vout() const {
		return out();
	}
};
class Derived : public Base {
private:
	string name;
public:
	Derived() = default;
	Derived(int value, string name) : Base(value), name{ name } {}
	string out() const {
		stringstream ss;
		ss << "Derived(" << Base::out() << ", " << name << ")";
		return ss.str();
	}
	string vout() const override { return out(); }
};

static void handle(const Base b) {
	cout << "\tcall to out with slicing -> " << b.out() << endl;
	cout << "\tcall to vout with slicing -> " << b.vout() << endl;
}
static void ref_handle(const Base& b) {
	cout << "\tcall to out -> " << b.out() << endl;
	cout << "\tcall to vout() -> " << b.vout() << endl;
}
int main()
{
	Base b{ 1 };
	Derived d{ 2, "Derived" };
	cout << "handle(const Base) with argument Base -> " << endl; handle(b);
	cout << "handle(const Base) with argument Derived -> " << endl; handle(d);
	cout << "ref_handle(const Base&) with argument Base& -> " << endl; ref_handle(b);
	cout << "ref_handle(const Base&) with argument Derived& -> " << endl; ref_handle(d);
}
