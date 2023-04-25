#include <iostream>
#include <mutex>
#include <vector>

/*
* Class Template Argument Deduction (CTAD)
* 
* Until C++14, template argument deduction only worked with functions and not classes. To create instances of classes with template arguments, we had to call make functions,
* for example, make_pair.
* 
* In C++17, the deduction also works with classes, called CTAD. There are 2 types, compiler generated and user defined.
* 
* Works with direct or copy initialization of objects or objects on the heap.
*/

template<typename T>
class Data {
public:
	Data(const T &t) {
		
	}
};
Data(const char *) -> Data<std::string> ; //user defined deduction guide, changes from compiler generated for const char* to string (reflected in d5 for example)
Data(int)->Data<long> ; //same as before but for long
int main() {

	Data d1{5} ;//New way
	Data d2{8.2f} ;//New way

	Data d3 = d1 ;//New way
	auto d4 = new Data{"Hello"} ;//New way with objectd on the heap

	Data d5{"Hello"} ;

	Data d6{ 5 };

	//Old way
	std::pair<int,int> p1{2,5} ;
	auto p2 = std::make_pair(2,5) ;
	//New way without template specification
	std::pair p3{2,5} ;
	std::vector v1{1,2,3,4} ;

	std::mutex m ;
	std::lock_guard lck{m} ;
	
}
