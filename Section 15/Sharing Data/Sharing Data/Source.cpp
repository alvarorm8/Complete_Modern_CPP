#include <iostream>
#include <list>
#include <thread>
#include <string>
#include <mutex>
/*
* Data sharing between threads.
* 
* 1. We can make the variables as global to access them for every thread.
* 
* But the problem is that with several threads accessing at the same time to the same
* varibles, problems will happen and the data won't be what we want.
* 
* To solve it, we can use mutex to lock variables in one thread. But only one thread can
* block it simultaneously. If another tries to block it, the thread will be put in a wait queu.
* 
* Using mutex with lock and unlock functions is dangerous, if some exception happens and the unlock
* function is not called, the variables will be blocked, with a possibility that the program will be frozen.

* That's why we have to use std::lock_guard, a class included in C++11, which manages the blocking and unblocking
* of the resources and variables.
* 
* This solution is not optimal because while one thread is doing work blocking resources, the other is sleeping, so the performance
* is not as good as it could be. So blocking should be avoided as much as possible. The best solution is that each thread has its own
* variables and then we catch the result in the main.
* There is not an easy way to get the variables from the thread using thread class, instead, we can use high level concurrency (seen in Async solution).
*/
std::list<int> g_Data;
const int SIZE = 10000;
std::mutex g_Mutex;
void Download() {
	for (int i = 0; i < SIZE; ++i) {
		//Use std::lock_guard to lock a mutex (RAII)
		std::lock_guard<std::mutex> mtx(g_Mutex);
		g_Data.push_back(i);
		if (i == 500)
			return;
	}
}
void Download2() {
	for (int i = 0; i < SIZE; ++i) {
		std::lock_guard<std::mutex> mtx(g_Mutex);
		g_Data.push_back(i);
	}
}
int main() {
	std::thread thDownloader(Download);
	std::thread thDownloader2(Download2);
	thDownloader.join();
	thDownloader2.join();
	std::cout << g_Data.size() << std::endl; 
	return 0;
}