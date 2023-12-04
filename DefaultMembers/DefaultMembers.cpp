#include <iostream>
#include <string>
using namespace std;

class Sample {
	int x = 0;
	int j = 0;
	string s;
public:
	Sample() = default;
	Sample(string text, int x, int j) :x{ x }, j{ j }, s{ text } {}

	inline int getX() const { return x; }
	inline string getS() const { return s; }
	inline int getJ() const { return j; }
};


int main()
{
	Sample sample;
	cout << "|" << sample.getS() << "|" << sample.getX() << " " << sample.getJ() << endl;
}
