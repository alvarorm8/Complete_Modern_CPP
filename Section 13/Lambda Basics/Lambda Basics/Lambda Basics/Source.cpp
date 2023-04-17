#include <iostream>
/*
* As said in Function Pointers solution, in C++11 lambda expressions substitute function objects and function pointers.
* 
* They define an anonymous function object but without having to define a structure and overloading the function operator.
* That operation is done internally by the compiler, a class is defined and the function operator is overloaded.
* It's like a shortcut. They can be passed as an argument to functions that accepts function objects and it's a function,
* it accepts arguments and returns a return type. 
*
* They also can be passed to a function that accepts a function pointer, because internally the compiler sythesizes a 
* type conversion operator, which returns a function pointer to a static function inside the lambda created which invokes the call to the lambda 
* function operator overloaded. It's important for that that the capture clause is empty (capture clause is explained below and in CaptureList solution),
* if it's not empty the type conversion operator is not created.
* 
* To give a lambda a name, we use the auto keyword. The syntax is:
* 
* [](<args>)<mutable> <excp specification> -> <return type>
* {
* };
* 
* 1. []: lambda introducer, contains a capture clause. We can use it to pass variables to the lambda. This is seen at CaptureList solution.
* 2. (<args>): arguments, optional
* 3. <mutable>: mutable specification, optional.
* 4. <excp specification>: exception specification
* 5. -> <return type>: trailing return type, optional. Return type is optional if the function
* returns variables of the same type or if it return void. If it returns the sum of a float 
* and an int for example, the return type has to be specified. 
* 6. {}: lambda body.
*/
//Possible implementation of a lambda expression as a function object
template<typename T>
struct Unnamed {
	T operator()(T x, T y)const {
		return x + y;
	}
};
int main() {
	/*[]() {
		std::cout << "Welcome to Lambda expressions" << std::endl;
	}();
	With the last () we call the anonymous lambda expression.
	*/
	//Compiler automatically creates a function object
	auto fn = []() {
		std::cout << "Welcome to Lambda expressions" << std::endl ;
	};
	fn(); //call lambda expression
	std::cout << typeid(fn).name() << std::endl; //internally, the type is a class
	//Generic/polymorphic lambda using auto (introduced in C++14)
	//							  <optional specifiers>
	auto sum = [](auto x, auto y)/*mutable*/ /*noexcept(false)*/ {
		return x + y;			//	^^^^		^^^^
	};
	Unnamed<int> n;
	std::cout << "Sum is:" << n(5.5f, 2.2f) << std::endl; //use of function object instead of lambda
	std::cout << "Sum is:" << sum(5.5f, 2.2f) << std::endl;
	return 0;
}