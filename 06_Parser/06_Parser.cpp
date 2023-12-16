// Implementare un parser di espressioni aritmetiche
#include <iostream>
#include <string>
#include "Parser.h"

using std::string_literals::operator""s;

int main()
{
	Parser p;
	auto expr = "1,1 + 22,2 - 3 * 4,01"s;
	std::cout << expr << " = " << p.process(expr) << std::endl;
}