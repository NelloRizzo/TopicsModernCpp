#include <iostream>
#include "OrderedList.h"

class My {
	int value;

	friend std::ostream& operator <<(std::ostream&, const My&);
public:
	My(int value) :value{ value } {}

	bool operator<(const My& other) { return value < other.value; }
	bool operator>(const My& other) { return value > other.value; }
};

static std::ostream& operator <<(std::ostream& s, const My& m) { return s << "My(" << m.value << ')'; }

int main()
{
	OrderedList<My> l{};
	l.append(My{ 3 });
	l.append(My{ 1 });
	l.append(My{ 4 });
	l.append(My{ 2 });
	My m10 = My{ -10 };
	l.append(m10);
	My m11 = My{ -11 };
	l.append(std::move(m11));
	l.visit([](My&& i) {std::cout << "Elemento: " << i << std::endl; });
}