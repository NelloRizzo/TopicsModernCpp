#include <iostream>
#include "LinkedList.h"

struct My {
	int value;
	static friend std::ostream& operator<<(std::ostream& s, const My& m) {
		return s << "My(" << m.value << ")";
	}
};

class PrintFunctor : public Functor<My> {
public:
	void operator()(const My* item) override {
		std::cout << "Found: " << *item << std::endl;
	}
};

int main()
{
	LinkedList<My> l{};
	l.append(new My{ 10 });
	l.append(new My{ 20 });
	l.append(new My{ 30 });

	l.navigate(PrintFunctor{});
	PrintFunctor pf;
	l.navigate(pf);
	l.navigate(
		[](const My* item) 
		{ std::cout << "My(" << item->value << ")" << std::endl; }
	);

	std::cout << "Min: ";
	int min; std::cin >> min;
	std::cout << "Max: ";
	int max; std::cin >> max;
	std::cout << "Search in the list:" << std::endl;
	l.navigate(
		[=](const My* item)
		{ 
			if (item->value >= min && item->value <= max) std::cout << *item << std::endl;
		}
	);
}