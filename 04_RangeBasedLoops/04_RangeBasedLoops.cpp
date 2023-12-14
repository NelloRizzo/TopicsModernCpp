#include <iostream>
#include <vector>
using namespace std;

class My {
private:
	int value;
public:
	My(int v) : value{ v } { cout << "Costruttore di " << *this << endl; }
	My(const My& m) : value{ m.value } { cout << "Costruttore di copia per " << *this << endl; }
	My& operator=(const My& m) {
		value = m.value;
		return *this;
	}
	inline int getValue() const { return value; }
	inline void incValue() { ++value; }

	static friend ostream& operator<<(ostream& s, const My& m) {
		return s << "My(" << m.value << ')';
	}
};

int main()
{
	auto v = vector<int>{ 32,3456,478,12543,54867,23564,5987,3456,5896 };
	cout << "Items in vector incremented by 1" << endl;
	for (auto c : v)
		cout << ++c << endl;
	cout << "Items in vector after increment" << endl;
	for (auto c : v)
		cout << c << endl;
	cout << "Items as reference in vector incremented by 1" << endl;
	for (auto& c : v)
		cout << ++c << endl;
	cout << "Items in vector after increment" << endl;
	for (auto c : v)
		cout << c << endl;

	auto vm = vector<My>{ My{1}, My{2}, My{3} };
	for (auto& m : vm) {
		m.incValue();
		cout << m << endl;
	}
	for (const auto& m : vm) {
	//for (auto m : vm) {
		cout << m << endl;
	}
}