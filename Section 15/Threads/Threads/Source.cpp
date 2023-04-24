#include <iostream>
#include <list>
#include <thread>
#include <string>

/*
* When we create a thread, we pass it a callable as argument to the constructor (callback).
* It does not wait for the thread to start and returns inmediatelly.
* 
* Always we have to join the thread, if not, when the main thread finishes, if the thread has not finished
* then the object will be destroyed and the process whic it was doing will remain unfinished.
* 
* If we don't want to wait for the thread (because it takes much time), we can detach it, and make it non joinable. But if the program
* finishes its execution, the thread will die anyway without finishing its tasks.
* 
* A detached thread will release all its resources once it finishes its execution.
* 
* The constructor of a thread is a variadic template, so it can accept many arguments. The first one always has to be a callable.
* If we want to pass a variable as reference, we have to use std::ref and std::cref to pass arguments as reference & const reference, respectively.
* If we don't use it, another variable will be created inside the thread by copy.
*/
std::list<int> g_Data;
const int SIZE = 5000000;
class String {
public:
	String() {
		std::cout << "String()" << std::endl;
	}
	String(const String &) {
		std::cout << "String(const String&)" << std::endl;
	}
	String & operator=(const String&) {
		std::cout << "operator=(const String&)" << std::endl;

		return *this;
	}
	~String() {
		std::cout << "~String()" << std::endl;
	}
};
void Download(const String &file) {
	//std::cout << "[Downloader]Started download of file :" << file << std::endl; 
	for (int i = 0; i < SIZE; ++i) {
		g_Data.push_back(i);
	}
	std::cout << "[Downloader]Finished download" << std::endl; 
}
int main() {
	String file{};
	std::cout << "[main]User started an operation" << std::endl; 
	//use std::ref and std::cref to pass arguments as reference & const reference, respectively.
	std::thread thDownloader(Download,std::cref(file) );
	//thDownloader.detach(); //detach thread to not wait for it to finish  

	std::cout << "[main]User started another operation" << std::endl;
	//Always check before joining a thread
	if (thDownloader.joinable()) {
		thDownloader.join() ; //makes the main thread to wait for the thread thDownloader to finish
	}
	//system("Pause"); //call pause to make the app wait until the detached thread finishes
	return 0;
}