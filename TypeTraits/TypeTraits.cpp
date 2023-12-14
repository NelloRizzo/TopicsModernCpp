#include <iostream>
#include <string>
#include <type_traits>
#include <iomanip>

template<class T>
void out(T v) {
	std::cout << std::boolalpha;

	std::cout << "Qui devo gestire un intero: " << v << '\t' << std::is_integral<T>::value
		<< std::endl;
	static_assert(std::is_integral<T>::value, "Qui serve un intero");
}

class A {};
class B :public A {};

template<class T>
void handle(T& a) {
	static_assert(std::is_base_of<A, T>(), "Solo derivati da A");
	std::cout << "Handling " << typeid(decltype(a)).name() << std::endl;
}

template<class T>
concept DerivedFromA = std::is_base_of<A, T>::value; 

template<DerivedFromA T>
void handle_with_concept(T a) {
	std::cout << "Handling " << typeid(decltype(a)).name() << std::endl;
}

int main()
{
	//out("Ciao");
	//out(1.3);
	out(1);
	A a;
	B b;
	int i = 10;
	handle(a);
	handle(b);
	// handle(i);
	handle_with_concept(a);
	handle_with_concept(b);
	// handle_with_concept(i);
}
