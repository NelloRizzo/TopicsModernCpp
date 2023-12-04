#include <sstream>
#include "Ratio.h"
namespace ratio {

	int Ratio::gcf(int a, int b) {
		if (a < b) { int t = a; a = b; b = t; }

		if (b == 0) return a;
		return gcf(b, a % b);
	}

	Ratio::Ratio() :Ratio(0) {}

	Ratio::Ratio(float n) :Ratio{ static_cast<int>(n * 10000), 10000 } {}

	Ratio::Ratio(int numerator, int denominator) : numerator{ abs(numerator) }, denominator{ abs(denominator) }, signum{ (numerator * denominator) >= 0 ? 1 : -1 } {
		int gcf = this->gcf(this->numerator, this->denominator);
		this->numerator /= gcf;
		this->denominator /= gcf;
		cout << "Constructor" << endl;
	}

	Ratio::Ratio(string r)
	{
		stringstream ss{ r };
		int n = 1; ss >> n;
		ss.get(); // ratio operator /
		int d = 1; ss >> d;
		signum = n * d >= 0 ? 1 : -1;
		n = abs(n);
		d = abs(d);
		int gcf = this->gcf(n, d);
		numerator = n / gcf;
		denominator = d / gcf;
	}

	Ratio::Ratio(const Ratio& r) :Ratio(r.signum* r.numerator, r.denominator)
	{
		cout << "Ratio copy constructor" << endl;
	}

	Ratio& Ratio::operator=(const Ratio& r)
	{
		signum = r.signum;
		numerator = r.numerator;
		denominator = r.denominator;
		cout << "Ratio copy assignment" << endl;
		return *this;
	}

	Ratio& Ratio::operator=(Ratio&& r) noexcept
	{
		signum = r.signum;
		numerator = r.numerator;
		denominator = r.denominator;
		cout << "Ratio move assignment" << endl;
		return *this;
	}

	Ratio::Ratio(Ratio&& r) noexcept :Ratio(r.signum* r.numerator, r.denominator)
	{
		cout << "Ratio move constructor" << endl;
	}

	Ratio Ratio::operator+() const { return Ratio{ signum * numerator, denominator }; }

	Ratio Ratio::operator-() const { return Ratio{ -signum * numerator, denominator }; }

	Ratio Ratio::inverse() const { return Ratio{ signum * denominator, numerator }; }

	Ratio::operator string()const
	{
		stringstream s;
		if (numerator == 0) return "0";
		if (signum == -1) s << '-';
		s << numerator;
		if (denominator != 1) s << '/' << denominator;
		return s.str();
	}

	Ratio::operator float() const { return 1.0f * signum * numerator / denominator; }

	ostream& operator<<(ostream& s, const Ratio& r) { return s << (string)r; }

	Ratio operator+(const Ratio& r1, const Ratio& r2)
	{
		return Ratio{ r1.signum * r1.numerator * r2.denominator + r2.signum * r2.numerator * r1.denominator, r1.denominator * r2.denominator };
	}

	Ratio operator+(string r1, const Ratio& r2) { return Ratio{ r1 } + r2; }

	Ratio operator-(const Ratio& r1, const Ratio& r2) { return r1 + -r2; }

	Ratio operator*(const Ratio& r1, const Ratio& r2)
	{
		return Ratio{ r1.signum * r2.signum * r1.numerator * r2.numerator, r2.denominator * r1.denominator };
	}

	Ratio operator/(const Ratio& r1, const Ratio& r2) { return r1 * r2.inverse(); }
}