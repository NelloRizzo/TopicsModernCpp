#include <iostream>

struct My {
public:
	int x = 0;
	int y = 1;
public:
	My(int x, int y) : x{ x }, y{ y } {}

	static friend std::ostream& operator<<(std::ostream& s, My my) {
		return s << "My(" << my.x << "," << my.y << ")";
	}
};

int main()
{
	My my{ 123, 4234 };
	auto [a, b] = my;
	std::cout << my << ' ' << a << ',' << b << std::endl;
}
