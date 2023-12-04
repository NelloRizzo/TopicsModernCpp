#include <iostream>
#include <vector>
using namespace std;
int main()
{
	auto v = vector<int>{ 32,3456,478,12543,54867,23564,5987,3456,5896 };
	cout << "Items in vector incremented by 1" << endl;
	for (auto c : v)
		cout << ++c << endl;
	cout << "Items as reference in vector incremented by 1" << endl;
	for (auto& c : v)
		cout << ++c << endl;
	cout << "Items in vector after increment" << endl;
	for (auto c : v)
		cout << c << endl;
}