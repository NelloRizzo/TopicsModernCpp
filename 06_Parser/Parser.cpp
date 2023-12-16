#include "Parser.h"
#include <iostream>
#include <sstream>

static constexpr bool is_digit_or_comma(char c) { return (c >= '0' && c <= '9') || c == ','; }
static constexpr bool is_operator(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }

static double parse_number(std::stringstream& s) {
	std::string n;
	while (!s.eof() && s.peek() == ' ') s.get(); // skip spaces
	while (!s.eof() && is_digit_or_comma(s.peek())) {
		char ch = s.get();
		if (ch == ',') ch = '.';
		if (ch != '.' || n.find('.') == -1)
			n += ch;
	}
	return atof(n.c_str());
}

double Parser::process(std::string expression)
{
	std::stringstream ss(expression);
	char op = '=';
	double accumulator = 0;
	while (!ss.eof()) {
		double value = parse_number(ss);
		while (!ss.eof() && ss.peek() == ' ') ss.get(); // skip spaces
		char o = ss.get();
		switch (op)
		{
		case'+':
			accumulator += value;
			break;
		case'-':
			accumulator -= value;
			break;
		case'/':
			accumulator /= value;
			break;
		case'*':
			accumulator *= value;
			break;
		default:
			accumulator = value;
			break;
		}
		op = o;
	}
	return accumulator;
}
