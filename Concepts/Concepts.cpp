#include <iostream>
#include <string>
using namespace std;

template<class S>
concept Streameable = requires(ostream & os, S s) { { os << s } -> convertible_to<ostream&>; };

template<Streameable S>
//template<class S>
void print(string message, S s) {
	cout << message << ":\t" << s << endl;
}

template<class T>
concept Incrementable = requires(T i) { { i++ } -> std::same_as<T>; };

template<class T>
	requires Incrementable<T>
void increment(T& t) {
	cout <<"Increment: " << ++t << endl;
}

class My {
public:
	int value;

	friend ostream& operator <<(ostream& s, const My& m) {
		return s << "My(" << m.value << ')';
	}
	My operator++() { ++value; return *this; }
	My operator++(int) { auto old = *this; ++value; return old; }
	My operator--() { --value; return *this; }
	My operator--(int) { auto old = *this; --value; return old; }
};

int main()
{
	int x = 10;
	print("Stampa di un intero: ", x);
	string s{ "Ciao" };
	print("Stampa di una stringa", s);

	My my{ 10 };
	print("Stampa di my: ", my);
	increment(x);
	increment(my);
	print("Stampa di my: ", my);

}
