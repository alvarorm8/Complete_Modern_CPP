#include <iostream>
#include <memory>
#include <vector>
class A {
public:
	A() {
		std::cout << "A()" << std::endl;
	}
	~A() {
		std::cout << "~A()" << std::endl;
	}
};
class B {
public:
	B() {
		std::cout << "B()" << std::endl;
	}
	~B() {
		std::cout << "~B()" << std::endl;
	}
};
/*
* If during the construction of an object, something fails, the only way to indicate it is
* by throwing an exception. In that case, the destructor is not called, but all memory for
* the objects created is freed. If we have resources like raw pointers, these will not be 
* released, so there will be memory leaks.
* 
* To solve it, we can replace those resources with modern C++ objects, like smart pointers,
* vectors to replace arrays, strings, etc. These objects will be released if the constructor
* fails.
* 
* In the destructor no exception should be thrown, because if it happens it can lead to the program
* crashing. For example, if the destructor is called through stack unwinding coming from an exception
* and the destructor throws an exception, the program will terminate.
*/
class Test {
	std::unique_ptr<A> pA{};
	B b{};
	std::unique_ptr<int> pInt{};
	std::string pStr{};
	std::vector<int> pArr{};
public:
	Test() { 
		std::cout << "Test():Acquire resources" << std::endl;
		pA.reset(new A);
		throw std::runtime_error("Failed to initialize");
		/*pA = new A;
		pInt = new int;
		pStr = new char[1000];
		pArr = new int[50000];*/
	}
	~Test() {  
		std::cout << "~Test():Release resources" << std::endl; 
		//throw std::runtime_error("Failed to initialize");
		/*delete pA;
		delete pInt;
		delete[]pStr;
		delete[] pArr;*/
	}
};

int main() {
	try {
		Test t;
		//throw std::runtime_error{ "Exception" };
	}
	catch (std::runtime_error &ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}