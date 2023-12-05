#include <iostream>
#include "ListImplementation.h"

struct My {
	int value;
	static friend std::ostream& operator<<(std::ostream& s, const My& m) {
		return s << "My(" << m.value << ")";
	}
};

class PrintFunctor : public Functor<My> {
public:
	void operator()(const My* item) override { std::cout << "Found: " << *item << std::endl; }
};

int main()
{
	List<My> l{};
	l.append(My{ 10 });
	l.append(My{ 20 });
	l.append(My{ 30 });
	My m1{ 21 };
	//l.append(m1); // error
	l.append(std::move(m1));
	My m2{ 22 };
	l.emplace_back(m2);
	My* m3 = new My{ 23 };
	//l.append(*m3); // error
	l.emplace_back(*m3);
	l.emplace_back(My{ 24 });

	l.navigate(PrintFunctor{});
	l.navigate([](const My* item) { std::cout << "My(" << item->value << ")" << std::endl; });

	std::cout << "Search in the list:" << std::endl;
	l.navigate([](const My* item) { if (item->value < 30 && item->value > 10) std::cout << *item << std::endl; });
}
