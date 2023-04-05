#include <iostream>
/*
* noexcept is applied both in declaration and in the definition of the functions.
* 
* It can optimize the code at compilation, for example, no stack unwinding will be generated.
* 
* We have to be very sure that no exception will be thrown, because if we mark a function and 
* it throws an exception, the program will terminate.
* 
* noexcept accepts a boolean as parameter. By default, the parameter is true.
* 
* In general, if a function calls a library function, like std::cout, we can not assure that 
* function won't throw any exception, so we have to leave it as neutral.
* 
* IMPORTANT TIP: In move constructor and move assignment operator, we should mark them with 
* the noexcept keyword since it will improve the performance of the code.
*/
void Test(int x)noexcept(false) {
	std::cout << x << std::endl;
	//throw x;
}
int Sum(int x, int y)noexcept(noexcept(Test(x))) {
	Test(x);
	return x + y;
}
class A {
public:
	//Destructors are implicitly noexcept(true) in C++11
	~A() {
		throw 3; 
	}
};
int main() {
	A a;
	//boolalpha manipulator prints 0 & 1 as false & true
	std::cout << std::boolalpha << noexcept(Test(3)) << std::endl;
	std::cout << std::boolalpha << noexcept(a.~A()) << std::endl;
	try {
		Sum(3, 5);
		//Other statements
	}
	catch (int x) {
		std::cout << x << std::endl ;
	}
}