#include <future>
#include <iostream>
#include <thread>
/*
* A promise provides a way to store a value or an exception, which is called shared state. This state can be accessed later from another thread through a future object.
* 
* promise/future are like two endpoints of a communication channel, one stores the value in a promise and the other retrieves it through a future object asynchronoulsy.
* These operations are synchronized, so they are thread safe. This way, we can share data between threads without synchronizing them.
* 
* Promise object can be used only once.
* 
* As soon as the shared state is set in the thread with a promise, this data travels through the communication channel to the thread of the future object, so it is available. 
* Once the value is get, the shared state is destroyed, so we can't call get() again in a future object.
* 
* Promise and future are non-copiable, so if we want to pass to a function, it has to be as a reference.
* 
* In this example, we use promise to notify the task thread which executes Operation when the data passed to it is ready.
* 
* If we throw an exception in one thread, it can be shared with the other thread with the promise. This can be done setting an exception pointer in the promise.
* An exception pointer is like a shared pointer for exceptions.
* 
* The reverse operation is also possible, you can throw an exception in the task thread and get it on the main thread. In this case, only throw the exception, no need to create the 
* exception pointer. In the main thread, we can catch it with the get() method. This is done in the assignment function below.
*/

int Assignment1(int count) {
	using namespace std::chrono_literals; //included in C++14 to use sleep_for(1s) as std::chrono::seconds(1) for example
	int sum{};
	for (int i = 0; i < count; ++i) {
		if (i == 5) { //manually throw exception 
			std::cout << "[Assignment1] Throwing exception" << std::endl;
			throw std::runtime_error{ "Error in Assignment1 function!!" };
		}
		sum += i;
		std::cout << '.';
		std::this_thread::sleep_for(300ms);
	}
	return sum;
}

void CallAssignment1() {
	using namespace std::chrono_literals;
	std::future<int> result = std::async(std::launch::async, Assignment1, 10);
	std::cout << "Calling the Assignment1 function" << std::endl;
	try {
		if (result.valid()) {
			auto sum = result.get();
			std::cout << "Result from the Assignment function: " << sum << std::endl;
		}
	}
	catch (std::exception& ex) {
		std::cout << "[CallAssignment] Exception received:" << ex.what() << std::endl;
	}
}

int Operation(std::promise<int> & data) {
	using namespace std::chrono_literals;
	auto f = data.get_future() ; //gets future from promise
	try {
		std::cout << "[Task] Waiting for count\n";
		auto count = f.get(); //wait for the data to be ready
		std::cout << "[Task] Count acquired.\n";
		int sum{};
		for (int i = 0; i < count; ++i) {
			sum += i;
			std::cout << '.';
			std::this_thread::sleep_for(300ms);//std::chrono::seconds(1) 
		}
		return sum;
	}catch(std::exception &ex) {
		std::cout << "[Task] Exception:" << ex.what() << std::endl; //gets the exception thrown in main thread
	}
}

void CallOperation() {
	using namespace std::chrono_literals;
	bool throwException = true;
	std::promise<int> data;
	std::future<int> result = std::async(std::launch::async, Operation, std::ref(data));
	std::this_thread::sleep_for(1s);
	std::cout << "[main] Setting the data in promise\n";
	try {
		if (throwException)
			throw std::runtime_error{ "Data not available" };//manually throw the exception to force exception sharing between threads with promises
		data.set_value(10); //set value in the promise so in Operation thread can be obtained
		if (result.valid()) {
			auto sum = result.get();
			std::cout << sum << std::endl;
		}
	}
	catch (std::exception& ex) {
		data.set_exception(std::make_exception_ptr(ex));//set exception pointer in the promise to share it with the thread executing Operation
	}
}
int main() {
	bool operation = false;

	if (operation)
		CallOperation();
	else
		CallAssignment1();
}