#include <iostream>
#include <memory>
#include <vector>
#include <random>
class Test {
public:
	Test() { std::cout << "Test():Acquire resources" << std::endl; }
	~Test() { std::cout << "~Test():Release resources" << std::endl; }
};

void ProcessRecords(int count) {
	std::unique_ptr<Test> t(new Test);
	if (count < 10)
		throw std::out_of_range("Count should be greater than 10");

	std::vector<int> p;
	p.reserve(count);
	std::vector<int> records;
	records.reserve(count);
	//Process the records
	for (int i = 0; i < count; ++i) {
		records.push_back(i);
	}
	std::default_random_engine eng;
	std::bernoulli_distribution dist;
	int errors{};
	for (int i = 0; i < count; ++i) {
		try {
			std::cout << "Processing record # : " << i << " ";
			if (!dist(eng)) {
				++errors;
				throw std::runtime_error("Could not process the record");
			}
			std::cout << std::endl;
		}
		catch (std::runtime_error &ex) {
			std::cout << "[ERROR " << ex.what() << "]" << std::endl;
			if (errors > 4) {
				std::runtime_error err("Too many errors. Abandoning operation");
				ex = err;//since ex is a reference, we modify the original error
				throw;//rethrow the error outside the local try-catch. If we don't modify the error, it will throw the same error.
			}
		}
	}
}
/*
Old code using raw pointers
*/
void ProcessRecordsOld(int count) {
	/*
	Compare this code with the code that uses RAII.
	*/
	Test *t = new Test;
	if (count < 10)
		throw std::out_of_range("Count should be greater than 10");

	int *p = new int[count];
	int *pArray = (int*)malloc(count * sizeof(int));
	if (pArray == nullptr) {
		throw std::runtime_error("Failed to allocate memory");
	}
	//Process the records
	for (int i = 0; i < count; ++i) {
		pArray[i] = i;
	}
	//Unreachable code in case of an exception, memory leak
	free(pArray);
	delete[] p;
	delete t;

}
/*
* If an exception is thrown, all local objects created on the stack are destroyed. This is known as
* stack unwinding. But for objects created on the heap, this does not happen, and it will cause a memory
* leak.
* 
* To prevent this, we can use modern C++ features, like smart pointers or vectors. This will cause that stack unwinding
* destroys smart pointers, vectors, etc., since they are local objects, and, in that destruction, the destructors of the 
* resources that smart pointers hold will be called.
* 
* This is one important reason why modern C++ discourages the use of raw pointers.
*/
int main() {
	try {
		//ProcessRecords(std::numeric_limits<int>::max());
		ProcessRecords(10);
	}
	catch (std::runtime_error &ex) {
		std::cout << ex.what() << std::endl;
	}
	catch (std::out_of_range &ex) {
		std::cout << ex.what() << std::endl;
	}
	catch (std::bad_alloc &ex) {
		std::cout << ex.what() << std::endl;

	}

	/*
	std::exception is the base class for all standard
	exception classes. It can be used as a handler if
	the exception handling code is same for all child
	class exception objects
	*/
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}

	/*
	All-catch handler. Avoid as it does not give any
	information about the exception, so it is difficult
	to take any preventative action
	*/
	catch (...) {
		std::cout << "Exception" << std::endl;
	}
	return 0;
}

