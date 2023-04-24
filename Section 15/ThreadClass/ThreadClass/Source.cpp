#include <iostream>
#include <thread>
#include <Windows.h>
void Process() {
	//We can use std::this_thread to get ids, etc., in the thread
	//std::cout << "Threadid:" << std::this_thread::get_id() << std::endl;
	for (int i = 0; i < 10; ++i) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << i << ' ';
	}
}

int main() {
	std::thread t1(Process);
	//Returns the native type of the thread
	//On Windows the native type will be HANDLE
	HANDLE handle = t1.native_handle();
	//On Linux, the native type is pthread_t
	//pthread_t handle = t1.native_handle();

	//In C++ we can't name a thread but we can use the OS functions.
	//In Windows we have SetThreadDescription and in Linux we have pthread_setname_np. 
	//Here we have to include Windows.h to get the function
	SetThreadDescription(handle, L"MyThread");	
	//We can use this for debugging and identify our threads.

	//Gets the id of the thread
	auto id = t1.get_id();
	std::cout << "t1.get_id()" << id << std::endl;

	// Returns the number of cores that the CPU has. Ideally there should be one thread per core as maximum.
	int cores = std::thread::hardware_concurrency();

	std::cout << "Cores:" << cores << std::endl;
	t1.join();
	return 0;
}