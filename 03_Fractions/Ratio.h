#pragma once
#include <iostream>
using namespace std;

namespace ratio {

	class Ratio
	{
	private:
		int numerator;
		int denominator;
		int signum;
	public:
		static int gcf(int a, int b);

		Ratio();
		Ratio(int, int);
		Ratio(float);
		Ratio(string);

		Ratio(const Ratio&);
		Ratio(Ratio&&) noexcept;
		Ratio& operator=(const Ratio&);
		Ratio& operator=(Ratio&&) noexcept;

		Ratio operator+() const;
		Ratio operator-() const;
		Ratio inverse() const;

		explicit operator string() const;
		operator float() const;

		friend Ratio operator+(const Ratio& r1, const Ratio& r2);
		friend Ratio operator-(const Ratio& r1, const Ratio& r2);
		friend Ratio operator*(const Ratio& r1, const Ratio& r2);
		friend Ratio operator/(const Ratio& r1, const Ratio& r2);

		friend ostream& operator<<(ostream& s, const Ratio& r);
	};
}