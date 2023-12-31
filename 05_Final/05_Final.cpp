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
	// 3 = non inizio n� fine
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
	/* P */ "20002030200003230110200000",
	/* Q */ "00000000000000000000100000",
	/* R */ "23332330200333230333230023",
	/* S */ "23302220202222222032222000",
	/* T */ "20002000200000200003200000",
	/* U */ "21112030200003210111011111",
	/* V */ "20002000200000200000230000",
	/* W */ "20002000200000200000200000",
	/* X */ "20002000200000200000200000",
	/* Y */ "21112010211110211111211111",
	/* Z */ "20002000200000200000200003",
};

static bool isValid(const std::string word) {
	auto f = word.c_str();
	bool valid = true;
	auto len = word.length();
	auto i = f;
	for (auto i = 0; i < len - 1 && valid; ++i) {
		auto fc = std::tolower(word[i]);
		auto sc = std::tolower(word[i + 1]);
		auto c = valids[fc - 'a'][sc - 'a'];
		valid = c == '2' || ((i < len - 1) && c == '1') || ((i > 1 && i < len - 1) && c == '3');
	}
	return valid;
}

static Generator<std::string> anagrams(std::string word) {
	std::sort(word.begin(), word.end());
	do {
		if (isValid(word))
			co_yield word;
		//else
			//co_yield "INVALID " + word;
	} while (std::next_permutation(word.begin(), word.end()));
}

#include <coroutine>

int main()
{
	std::string s = "parola";

	auto a = anagrams(s);
	int counter = 0;
	while (a) {
		std::cout << ++counter << '\t' << a() << std::endl;
	}
}
