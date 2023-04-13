#include <iostream>
#include <type_traits>
/*
* This is a continuation of type_traits solution.
* 
* In the Divide function, which implementation in the previous solution is
* template<typename T>
* T Divide(T a, T b) {
*	 if(std::is_floating_point<T>::value == false) {
*		 std::cout << "Use floating point types only\n" ;
*	  	 return 0 ;
*	 }
*	 return a / b ;
* }
* 
* The std::is_floating_point<T>::value is evaluated at compile time, but the comparison with false is evaluated at runtime. 
* Since the information of floating point is known at compile time, we want to evaluate the comparison at compile time so +
* it is more efficient.
* 
* For this reason, static_assert can be used.
* 
* In C we have ASSERT macro, which evaluates an expression and if it's false, the program terminates. C++11 introduces static_assert
* to evaluate expressions and user defined messages at compile time. If the expression returns false, the compiler displays a message and
* the compilation fails.
* 
* For example:
* 
* static_assert(sizeof(void*)==4, "Compile only in 32-bit mode"); 
* 
* would check the compilation at compile time, and will fail if it's not that mode.
* 
* if (sizeof(void*) != 4) {
*	std::cout << "Not 32-bit mode";
*	return 0;
* }
* 
* This expression checks the same but at runtime, which is less efficient.
*/
template<typename T>
T Divide(T a, T b){
	static_assert(std::is_floating_point<T>::value, "Only floating point type supported") ; 
	//we change the if with the static_assert, so the following code is not necessary.
	/*if(std::is_floating_point<T>::value == false){
		std::cout << "Use floating point types only\n" ;
		return 0 ;
	}*/
	return a/b ;
}
int main(){
	std::cout 
	<< std::boolalpha
	<< "Is integer?" << std::is_integral<int>::value << std::endl;
	
	std::cout << Divide(5.1, 7.3) << std::endl ;
}