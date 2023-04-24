#include <future>
#include <iostream>
#include <thread>

/*
* C++ provides tools for high level concurrency. In this concurrency, we don't operate with threads but we operate with the functions
* we want to execute in a different thread. This is know as tasks level concurrency.
*
* To use this, we can use the async function, which accepts a callable as first argument, and then the arguments you want to pass to 
* the callable. As in threads, they're passed as values, to be passed by reference, use std::ref o std::cref.
* 
* Async returns an object of type future with the type of object the callable returns. In this example, an int, so it's much easier to get the value
* from the thread than using Thread class. std::future is created through a std::promise.
* 
* std::promise is an input channel
* std::future is an output channel
* 
* More info about promise/future in PromiseFuture solution.
* 
* With promise and future data sharing between threads is allowed safely without explicit synchronization.
* 
* Is important not to forget the return object, because if we don't catch it, the function will execute in the main thread, not in a separate one.
* 
* The function get makes the same as join for threads, it waits the function to finish the execution and gets the return value from the future object.
* 
* There's another argument which can be passed to async as first argument, second the callable and then the arguments. This first argument is a
* launch policy, which determines the behaviour of async.
* 
* std::launch::deferred -> task is executed synchronously in the main thread
* std::launch::async -> task is executed asynchronously. Creates a thread and executes the callable
* 
* The async function not always executes in a different thread, it depends on the compiler, etc., to force use std::launch::async and, if a thread can not be 
* created, the program will throw a std::system_error exception.
* 
* std::future has several wait functions:
* 1. wait() is like get(), but this doesn't get the result of the execution.
* 2. wait_for(), in which we specify an amount of time with td::chrono_literals. It returns an enum called future_status. It can have several statuses:
*	- std::future_status::deferred: we can not wait, the function executes synchronously
*	- std::future_status::ready: shared state is ready, you can call get()
*	- std::future_status::timeout: shared state is not ready, you can't call get() yet
* 3. wait_until(): it is like wait_for but accepts a timepoint.
*
*/

int Operation(int count) {
	using namespace std::chrono_literals; //included in C++14 to use sleep_for(1s) as std::chrono::seconds(1) for example
	int sum{};
	for (int i = 0; i < count; ++i) {
		sum += i;
		std::cout << '.';
		std::this_thread::sleep_for(300ms);
	}
	return sum;
}
int main() {
	using namespace std::chrono_literals;
	std::future<int> result = std::async(std::launch::async, Operation, 10);
	std::this_thread::sleep_for(1s);
	std::cout << "main() thread continues execution...\n";
	if (result.valid()) {
		auto timepoint = std::chrono::system_clock::now();
		timepoint += 1s;
		auto status = result.wait_until(timepoint);
		//auto status = result.wait_for(4s) ;
		switch (status) {
		case std::future_status::deferred:
			std::cout << "Task is synchronous\n";
			break;
		case std::future_status::ready:
			std::cout << "Result is ready\n";
			break;
		case std::future_status::timeout:
			std::cout << "Task is still running\n";
			break;
		}
		//result.wait() ;
		// Using std::launch::deferred makes that the function is executed at the moment we try to get the result from the future, this is, when we call the function get.
		// It's like calling Operation is this moment, like commented in the next line.
		//Operation(10) ;
		auto sum = result.get();
		std::cout << sum << std::endl;
	}
}