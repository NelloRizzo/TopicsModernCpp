// perfectForwarding1.cpp

#include <iostream>

namespace first_attempt {

	template <typename T, typename Arg>
	T create(Arg& a) {
		return T(a);
	}


	int main() {

		std::cout << std::endl;

		// Lvalues
		int five = 5;
		int myFive = create<int>(five);
		std::cout << "myFive: " << myFive << std::endl;

		// Rvalues
		// This dont compile due to rvalue 5 in the function call
		//int myFive2 = create<int>(5);
		//std::cout << "myFive2: " << myFive2 << std::endl;

		std::cout << std::endl;
		return 0;
	}
}
namespace second_attempt {
	template <typename T, typename Arg>
	T create(Arg& a) {
		return T(a);
	}

	template <typename T, typename Arg>
	T create(const Arg& a) {
		return T(a);
	}

	int main() {

		std::cout << std::endl;

		// Lvalues
		int five = 5;
		int myFive = create<int>(five);
		std::cout << "myFive: " << myFive << std::endl;

		// Rvalues
		int myFive2 = create<int>(5);
		std::cout << "myFive2: " << myFive2 << std::endl;

		std::cout << std::endl;
		return 0;
	}
}

namespace third_attempt {
	template <typename T, typename Arg>
	T create(Arg&& a) {
		return T(std::forward<Arg>(a));
	}

	int main() {

		std::cout << std::endl;

		// Lvalues
		int five = 5;
		int myFive = create<int>(five);
		std::cout << "myFive: " << myFive << std::endl;

		// Rvalues
		int myFive2 = create<int>(5);
		std::cout << "myFive2: " << myFive2 << std::endl;

		std::cout << std::endl;
		return 0;
	}
}

namespace expansion {
#include <iostream>

	void tprintf(const char* format) // base function called at the end of expansion
	{
		std::cout << " from base: `" << format << '`';
	}

	template<typename T, typename... Targs>
	void tprintf(const char* format, T value, Targs... Fargs) // recursive variadic function
	{
		for (; *format != '\0'; format++) // scan the format
		{
			if (*format == '%') // detect format placeholder and recall this tprintf
			{
				// put value param
				std::cout << value;
				// recursive call to this template
				tprintf(format + 1, Fargs...); 
				return;
			}
			// put next char
			std::cout << *format ;
		}
	}

	int main()
	{
		tprintf("% world% %\n", "Hello", '!', 123);
		return 0;
	}
}
int main() {
	second_attempt::main();
	third_attempt::main();
	expansion::main();
}