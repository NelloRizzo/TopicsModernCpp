#include <algorithm>
#include <iostream>
#include <string>
#include <coroutine>
#include <exception>

template<typename T>
struct Generator
{
	// The class name 'Generator' is our choice and it is not required for coroutine
	// magic. Compiler recognizes coroutine by the presence of 'co_yield' keyword.
	// You can use name 'MyGenerator' (or any other name) instead as long as you include
	// nested struct promise_type with 'MyGenerator get_return_object()' method.

	struct promise_type;
	using handle_type = std::coroutine_handle<promise_type>;

	struct promise_type // required
	{
		T value_;
		std::exception_ptr exception_;

		Generator get_return_object()
		{
			return Generator(handle_type::from_promise(*this));
		}
		std::suspend_always initial_suspend() { return {}; }
		std::suspend_always final_suspend() noexcept { return {}; }
		void unhandled_exception() { exception_ = std::current_exception(); } // saving exception

		template<std::convertible_to<T> From> // C++20 concept
		std::suspend_always yield_value(From&& from)
		{
			value_ = std::forward<From>(from); // caching the result in promise
			return {};
		}
		void return_void() {}
	};

	handle_type h_;

	Generator(handle_type h) : h_(h) {}
	~Generator() { h_.destroy(); }
	explicit operator bool()
	{
		fill(); // The only way to reliably find out whether or not we finished coroutine,
		// whether or not there is going to be a next value generated (co_yield)
		// in coroutine via C++ getter (operator () below) is to execute/resume
		// coroutine until the next co_yield point (or let it fall off end).
		// Then we store/cache result in promise to allow getter (operator() below
		// to grab it without executing coroutine).
		return !h_.done();
	}
	T operator()()
	{
		fill();
		full_ = false; // we are going to move out previously cached
		// result to make promise empty again
		return std::move(h_.promise().value_);
	}

private:
	bool full_ = false;

	void fill()
	{
		if (!full_)
		{
			h_();
			if (h_.promise().exception_)
				std::rethrow_exception(h_.promise().exception_);
			// propagate coroutine exception in called context

			full_ = true;
		}
	}
};

const std::string* valids = new std::string[]{
	// 0 = mai
	// 1 = non alla fine
	// 2 = sempre
	// 3 = non inizio né fine
	//       ABCDEFGHIJKLMNOPQRSTUVWXYZ
	/* A */ "01112110211111211111211111",
	/* B */ "23002000200100200100200000",
	/* C */ "20202001200100200100200000",
	/* D */ "20012000200000200100200000",
	/* E */ "21112110211111211111211111",
	/* F */ "20002300200100200100200000",
	/* G */ "20002030200101200100200000",
	/* H */ "20002000200000200000200000",
	/* I */ "21112110211111211111211111",
	/* J */ "20002000200000200000200000",
	/* K */ "20002000200000200000200000",
	/* L */ "23332300203330233033230023",
	/* M */ "23002000200030230000200000",
	/* N */ "20332030200003200033230003",
	/* O */ "21112010211110211111211111",
	/* P */ "20332030200003200033230003",
	/* Q */ "20332030200003200033230003",
	/* R */ "20332030200003200033230003",
	/* S */ "20332030200003200033230003",
	/* T */ "20332030200003200033230003",
	/* U */ "20332030200003200033230003",
	/* V */ "20332030200003200033230003",
	/* W */ "20332030200003200033230003",
	/* X */ "20332030200003200033230003",
	/* Y */ "20332030200003200033230003",
	/* Z */ "20332030200003200033230003",
};

static bool isValid(const std::string word) {
	auto f = word.c_str();
	bool valid = true;
	auto i = f;
	while (*i) {
		auto fc = std::tolower(*i);
		auto sc = std::tolower(*(i + 1));
		auto c = valids[fc - 'a'][sc - 'a'];
		i++;
	}
	return *i == 0;
}

static Generator<std::string> anagrams(std::string word) {
	std::sort(word.begin(), word.end());
	do {
		co_yield word;
	} while (std::next_permutation(word.begin(), word.end()));
}

int main()
{
	std::string s = "parola";

	auto a = anagrams(s);
	int counter = 0;
	while (a) {
		std::cout << ++counter << '\t' << a() << std::endl;
	}
}
