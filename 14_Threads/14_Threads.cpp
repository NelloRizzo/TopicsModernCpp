#include <chrono>
#include <iostream>
#include <thread>
#include <utility>
#include <atomic>
#include <vector>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <syncstream>

namespace thread_samples {
	void f1(int n)
	{
		for (int i = 0; i < 5; ++i)
		{
			std::cout << "Thread 1 executing\n";
			++n;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	void f2(int& n)
	{
		for (int i = 0; i < 5; ++i)
		{
			std::cout << "Thread 2 executing\n";
			++n;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	class foo
	{
	public:
		void bar()
		{
			for (int i = 0; i < 5; ++i)
			{
				std::cout << "Thread 3 executing\n";
				++n;
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}
		int n = 0;
	};

	class baz
	{
	public:
		void operator()()
		{
			for (int i = 0; i < 5; ++i)
			{
				std::cout << "Thread 4 executing\n";
				++n;
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}
		int n = 0;
	};

	int main()
	{
		std::cout << "***** thread sample" << std::endl;
		int n = 0;
		foo f;
		baz b;
		std::thread t1; // t1 is not a thread (no construction)
		std::thread t2(f1, n + 1); // pass by value
		std::thread t3(f2, std::ref(n)); // pass by reference
		std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread!!!
		std::thread t5(&foo::bar, &f); // t5 runs foo::bar() on object f
		std::thread t6(b); // t6 runs baz::operator() on a copy(!!!) of object b
		t2.join();
		t4.join();
		t5.join();
		t6.join();
		std::cout << "Final value of n is " << n << '\n';
		std::cout << "Final value of f.n (foo::n) is " << f.n << '\n';
		std::cout << "Final value of b.n (baz::n) is " << b.n << " (thread runs on a COPY of b!!!)\n";
		return 0;
	}
}

namespace jthread_samples {
	using namespace std::literals;

	void f1(int n)
	{
		for (int i = 0; i < 5; ++i)
		{
			std::cout << "Thread 1 executing\n";
			++n;
			std::this_thread::sleep_for(10ms);
		}
	}

	void f2(int& n)
	{
		for (int i = 0; i < 5; ++i)
		{
			std::cout << "Thread 2 executing\n";
			++n;
			std::this_thread::sleep_for(10ms);
		}
	}

	class foo
	{
	public:
		void bar()
		{
			for (int i = 0; i < 5; ++i)
			{
				std::cout << "Thread 3 executing\n";
				++n;
				std::this_thread::sleep_for(10ms);
			}
		}
		int n = 0;
	};

	class baz
	{
	public:
		void operator()()
		{
			for (int i = 0; i < 5; ++i)
			{
				std::cout << "Thread 4 executing\n";
				++n;
				std::this_thread::sleep_for(10ms);
			}
		}
		int n = 0;
	};

	int main()
	{
		std::cout << "\n***** jthread samples" << std::endl;
		int n = 0;
		foo f;
		baz b;
		std::jthread t0; // t0 is not a thread
		std::jthread t1(f1, n + 1); // pass by value
		std::jthread t2a(f2, std::ref(n)); // pass by reference
		std::jthread t2b(std::move(t2a)); // t2b is now running f2(). t2a is no longer a thread
		std::jthread t3(&foo::bar, &f); // t3 runs foo::bar() on object f
		std::jthread t4(b); // t4 runs baz::operator() on a copy of object b
		t1.join();
		t2b.join();
		t3.join();
		std::cout << "Final value of n is " << n << '\n';
		std::cout << "Final value of f.n (foo::n) is " << f.n << '\n';
		std::cout << "Final value of b.n (baz::n) is " << b.n << '\n';
		// t4 joins on destruction
		return 0;
	}
}
namespace atomic_samples {
	std::atomic_int acnt;
	int cnt;

	void f()
	{
		for (int n = 0; n < 10000; ++n)
		{
			++acnt;
			++cnt;
		}
	}

	int main()
	{
		std::cout << "\n***** Atomic operations" << std::endl;
		{
			std::vector<std::jthread> pool;
			for (int n = 0; n < 10; ++n)
				pool.emplace_back(f);
		}

		std::cout << "The atomic counter is " << acnt << '\n'
			<< "The non-atomic counter is " << cnt << '\n';
		return 0;
	}
}

namespace mutex_samples {

	std::map<std::string, std::string> g_pages;
	std::mutex g_pages_mutex;

	void save_page(const std::string& url)
	{
		// simulate a long page fetch
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::string result = "fake content";

		std::lock_guard<std::mutex> guard(g_pages_mutex);
		g_pages[url] = result;
	}

	int main()
	{
		std::cout << "\n***** Mutex samples" << std::endl;
		std::thread t1(save_page, "http://foo");
		std::thread t2(save_page, "http://bar");
		t1.join();
		t2.join();

		// safe to access g_pages without lock now, as the threads are joined
		for (const auto& pair : g_pages)
			std::cout << pair.first << " => " << pair.second << '\n';
		return 0;
	}
}
namespace shared_mutex_samples {
	class ThreadSafeCounter
	{
	public:
		ThreadSafeCounter() = default;

		// Multiple threads/readers can read the counter's value at the same time.
		unsigned int get() const
		{
			std::shared_lock lock(mutex_);
			return value_;
		}

		// Only one thread/writer can increment/write the counter's value.
		void increment()
		{
			std::unique_lock lock(mutex_);
			++value_;
		}

		// Only one thread/writer can reset/write the counter's value.
		void reset()
		{
			std::unique_lock lock(mutex_);
			value_ = 0;
		}

	private:
		mutable std::shared_mutex mutex_;
		unsigned int value_{};
	};

	int main()
	{
		ThreadSafeCounter counter;

		auto increment_and_print = [&counter]()
			{
				for (int i{}; i != 3; ++i)
				{
					counter.increment();
					std::osyncstream(std::cout)
						<< std::this_thread::get_id() << ' ' << counter.get() << '\n';
				}
			};

		std::thread thread1(increment_and_print);
		std::thread thread2(increment_and_print);

		thread1.join();
		thread2.join();
		return 0;
	}
}
int main() {
	thread_samples::main();
	jthread_samples::main();
	atomic_samples::main();
	mutex_samples::main();
	shared_mutex_samples::main();
}