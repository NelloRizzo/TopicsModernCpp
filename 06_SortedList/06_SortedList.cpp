#include <iostream>
#include "LinkedList.h"

struct My {
	int value;
	bool operator<(const My& m) const { return value < m.value; }
	bool operator>(const My& m) const { return value > m.value; }
	bool operator<=(const My& m) const { return value <= m.value; }
	bool operator>=(const My& m) const { return value >= m.value; }
	bool operator==(const My& m) const { return value == m.value; }
	bool operator!=(const My& m) const { return value != m.value; }
	static friend std::ostream& operator<<(std::ostream& s, const My& m) {
		return s << "My(" << m.value << ")";
	}
};

class PrintFunctor : public Functor<My> {
public:
	void operator()(const std::weak_ptr<My> item) override {
		auto p = item.lock();
		if (p)
			std::cout << "Found: " << *p << std::endl;
	}
};

int main()
{
	LinkedList<My> l{};
	auto a = My{ 10 };
	auto b = My{ 10 };
	auto c = My{ 10 };
	l.append(a);
	l.append(b);
	l.append(c);

	l.navigate(PrintFunctor{});
	l.navigate(
		[](const std::weak_ptr<My> item)
		{ std::cout << "My(" << item.lock()->value << ")" << std::endl; }
	);

	std::cout << "Min: ";
	int min; std::cin >> min;
	std::cout << "Max: ";
	int max; std::cin >> max;
	std::cout << "Search in the list:" << std::endl;
	l.navigate(
		[=](const std::weak_ptr<My> item)
		{
			auto p = item.lock();
			if (p)
				if (p->value >= min && p->value <= max) std::cout << *p << std::endl;
		}
	);
}