#include <iostream>
using namespace std;

class MyFunc {
private:
	float a, b;
public:
	MyFunc(float a, float b) : a{ a }, b{ b } {}
	float operator()(char op) {
		switch (op)
		{
		case '+': return a + b;
		case '-':return a - b;
		case '*': return a * b;
		case '/': return a / b;
		default:
			throw "exception";
		}
	}
};

int main()
{
	int i = 10;

	auto la = [](int x) -> int { return  x + 1; };
	cout << "la(" << i << ") = " << la(i) << endl;

	auto lb = [i](int x) -> int { return  x + i; };
	cout << "lb(3) = " << lb(3) << endl;

	auto lb1 = [=](int x) -> int { return  x + i; };
	cout << "lb1(3) = " << lb1(3) << endl;

	auto lc = [&ri = i](int x) -> int { return  x + ri++; };
	cout << "i = " << i << " lc(3) = " << lc(3) << " i = " << i << endl;

	auto ld = [&](int x) -> int { return  x + i++; };
	cout << "i = " << i << " ld(3) = " << ld(3) << " i = " << i << endl;

	cout << MyFunc{ 3,5 }('+') << endl;
	cout << MyFunc{ 3,5 }('*') << endl;
	cout << MyFunc{ 3,5 }('/') << endl;
	cout << MyFunc{ 3,5 }('-') << endl;
}
