#include <iostream>
#include <thread>
#include <coroutine>

struct promise;

struct my_coroutine : std::coroutine_handle<promise>
{
	using promise_type = ::promise;
};

struct promise
{
	my_coroutine get_return_object() { return { my_coroutine::from_promise(*this) }; }
	std::suspend_always initial_suspend() noexcept { return {}; }
	std::suspend_always final_suspend() noexcept { return {}; }
	void return_void() {}
	void unhandled_exception() {}
};

int main()
{
	auto c = [](int i) -> my_coroutine
		{
			std::cout << "Thread: " << std::this_thread::get_id() << '\t' << i << std::endl;
			co_return;
		}(10);
	std::cout << "Main Thread: " << std::this_thread::get_id() << std::endl;
	c.resume();
}
