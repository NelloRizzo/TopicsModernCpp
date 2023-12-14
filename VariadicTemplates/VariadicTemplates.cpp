#include <iostream>
#include <vector>
using namespace std;

class My {
	vector<int> v;

public:
	My(int start, int count) :v{} {
		for (auto i = 0; i < count; ++i) v.emplace_back(start + i);
	}
	My(int count) : v(count) {}
	My(const My&) = default;
	My& operator=(const My&) = default;
	My(My&&) = default;
	My& operator=(My&&) = default;

	static friend ostream& operator <<(ostream& s, const My& my) {
		s << "My({";
		for (const auto i : my.v) {
			s << i << ',';
		}
		return s << '\b' << "})";
	}
};

//static My factory(int start, int count) {
//	return My{ start, count };
//}
//static My factory(int count) {
//	return My{  count };
//}
template<class... T>
static My factory(T&&... params) {
	return My{ params... };
}

int main()
{
	My m1{ 10 };
	My m2{ 1,10 };
	cout << "m1 = " << m1 << endl;
	cout << "m2 = " << m2 << endl;

	m1 = factory(10, 20);
	m2 = factory(10);
	cout << "m1 = " << m1 << endl;
	cout << "m2 = " << m2 << endl;
	m2 = factory(m1);
	cout << "m2 = " << m2 << endl;
}