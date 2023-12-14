#include <chrono>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>
#include <future>
#include <mutex>
#include <string>

namespace promise_samples {
	static void accumulate(std::vector<int>::iterator first,
		std::vector<int>::iterator last,
		std::promise<int> accumulate_promise)
	{
		int sum = std::accumulate(first, last, 0);
		std::this_thread::sleep_for(std::chrono::seconds(2));
		accumulate_promise.set_value(sum); // Notify future
	}

	static void do_work(std::promise<void> barrier)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "Sending notification" << std::endl;
		barrier.set_value();
	}

	int main()
	{
		std::cout << "\n***** promises\n";
		// Demonstrate using promise<int> to transmit a result between threads.
		std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
		std::promise<int> accumulate_promise;
		std::future<int> accumulate_future = accumulate_promise.get_future();
		std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
			std::move(accumulate_promise));

		// future::get() will wait until the future has a valid result and retrieves it.
		// Calling wait() before get() is not needed
		// accumulate_future.wait(); // wait for result
		std::cout << "result=" << accumulate_future.get() << '\n';
		work_thread.join(); // wait for thread completion

		// Demonstrate using promise<void> to signal state between threads.
		std::promise<void> barrier;
		std::future<void> barrier_future = barrier.get_future();
		std::thread new_work_thread(do_work, std::move(barrier));
		barrier_future.wait();
		std::cout << "Notification received" << std::endl;
		new_work_thread.join();
		return 0;
	}
}

namespace packaged_task_samples {

	// unique function to avoid disambiguating the std::pow overload set
	static int f(int x, int y) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return static_cast<int>(std::pow(x, y));
	}

	static void task_lambda()
	{
		std::packaged_task<int(int, int)> task(
			[](int a, int b) {
				return static_cast<int>(std::pow(a, b));
			});

		std::future<int> result = task.get_future();

		task(2, 9);

		std::cout << "task_lambda:\t" << result.get() << '\n';
	}

	static void task_bind()
	{
		std::packaged_task<int()> task(std::bind(f, 2, 11));
		std::future<int> result = task.get_future();

		task();

		std::cout << "task_bind:\t" << result.get() << '\n';
	}

	static void task_thread()
	{
		std::packaged_task<int(int, int)> task(f);
		std::future<int> result = task.get_future();
		task(2, 10);
		std::cout << "task_thread:\t" << result.get() << '\n';
	}

	int main()
	{
		std::cout << "\n***** packaged tasks\n";
		task_lambda();
		task_bind();
		task_thread();
		return 0;
	}
}

namespace async_samples {
	std::mutex m;

	struct X
	{
		void foo(int i, const std::string& str)
		{
			std::lock_guard<std::mutex> lk(m);
			std::cout << str << ' ' << i << '\n';
		}

		void bar(const std::string& str)
		{
			std::lock_guard<std::mutex> lk(m);
			std::cout << str << '\n';
		}

		int operator()(int i)
		{
			std::lock_guard<std::mutex> lk(m);
			std::cout << i << '\n';
			return i + 10;
		}
	};

	template<typename RandomIt>
	int parallel_sum(RandomIt beg, RandomIt end)
	{
		std::cout << "Thread " <<
			std::this_thread::get_id() << "(" << *beg << "," << *(end - 1) << ")" << std::endl;
		auto len = end - beg;
		if (len < 10000)
			return std::accumulate(beg, end, 0);

		RandomIt mid = beg + len / 2;
		auto handle = std::async(std::launch::async, parallel_sum<RandomIt>, mid, end);
		int sum = parallel_sum(beg, mid);
		return sum + handle.get();
	}

	int main()
	{
		std::cout << "\n***** async\n";

		std::vector<int> v(100000); std::iota(v.begin(), v.end(), 0);
		std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';

		X x;
		// Calls (&x)->foo(42, "Hello") with default policy:
		// may print "Hello 42" concurrently or defer execution
		auto a1 = std::async(&X::foo, &x, 42, "Hello");
		// Calls x.bar("world!") with deferred policy
		// prints "world!" when a2.get() or a2.wait() is called
		auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
		// Calls X()(43); with async policy
		// prints "43" concurrently
		auto a3 = std::async(std::launch::async, X(), 43);
		a2.wait();                     // prints "world!"
		std::cout << a3.get() << '\n'; // prints "53"
		return 0;
	} // if a1 is not done at this point, destructor of a1 prints "Hello 42" here
}

int main() {
	//promise_samples::main();
	//packaged_task_samples::main();
	async_samples::main();
}