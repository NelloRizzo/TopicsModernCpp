#include <iostream>
#include <string>
#include <string_view>
#include <array>
using namespace std;

int main()
{
	constexpr int size = 10000;
	char* p = new char[size + 1];
	int c = 0;
	for (auto i = 0; i < size; ++i) p[i] = (c++ % 26) + 'a';
	p[size] = 0;
	string s{ p };
	cout << s << endl;
	string_view sv{ s.c_str() + 100, 200 };
	cout << sv << endl;
	std::array<char, 10> ch; ch.fill('\0');
	sv.copy(ch.data(), 9, 1);
	cout << ch.data() << endl;
	cout << sv.size() << endl;
}
