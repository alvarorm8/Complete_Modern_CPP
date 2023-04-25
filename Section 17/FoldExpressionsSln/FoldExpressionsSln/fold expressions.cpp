#include <iostream>

/*
* Folding is the process of applying a binary operator to a list of values recursively
* The results are combined recursively and with it, the final result is calculated
* 
* In C++11 we have variadic templates, but it requires to unpack the paremeters for processing and overload the template
* 
* In C++17 fold expressions are introduced, which reduces(fold) a parameter pack over a binary operator. We don't need to overload the variadic template, 
* this is a way to simplify variadic templates.
* 
* Syntax:
* 
* - (pack op ...) -> unary right fold (op is operator)
* - (... op pack) -> unary left old
* - (pack op ... op init) -> binary right old. init is the initial value, also called identity element
* - (init op ... op pack) -> binary left old
*/

//C++11 variadic template Sum
auto Sum() {
	return 0 ;
}
template<typename T, typename ...Args>
auto Sum(T a, Args...args) {
	return a + Sum(args...) ;
}
/*
 * Sum(1,2,3,4,5) ;
 * return 1 + Sum(2,3,4,5) ;
 * return 2 + Sum(3,4,5) ;
 * return 3 + Sum(4,5) ;
 * return 4 + Sum(5) ;
 * return 5 + Sum() ;
 * return 5 + 0 ;
 *
 *  1 + (2 + (3 + (4 + (5 + 0))))
 *  1 + (2 + (3 + (4 + 5)))
 *  1 + (2 + (3 + 9))
 *  1 + (2 + 12)
 *  1 + 14
 *  15
 * 
 */

template<typename...Args>
auto Sum2(Args...args) {
	//return (args + ...) ;   //Unary right fold
	return (... + args) ;   //Unary left fold
}

/*
 * Unary Right Fold
 * Sum2(1,2,3,4,5)
 * (1 +(2 + (3 + (4 + 5))))
 *
 * Unary Left Fold
 * ((((1 + 2) + 3) + 4) + 5)
 */

// If we call Sum2 like this Sum2(), it will give an error because there are no arguments, to solve it we can 
// use binary operators.

template<typename...Args>
auto Sum3(Args...args) {
	//return (0 + ... + args) ;   //Binary left fold
	return (args + ... + 0) ;   //Binary right fold
}

/*
 * Binary Right fold
 * 1 + (2 + (3 + (4 + (5 + 0))))
 *
 * Binary Left Fold
 * (((((0+1)+2) + 3) + 4) + 5)
 */

/*
* These are the operators we can use with fold expressions:
 + - * / % ^ & | = < > << >> += -
= *= /= %= ^= &= |= <<= >>= == != <= >= && || , .* ->*

Operator     Default value with empty parameters pack

&&          - true
||          - false
,           - void()
Others      - ill-formed
 */

template<typename...Args>
bool AnyOf(Args...args) {
	return (... || (args % 2 == 0)) ;
}
template<typename...Args>
bool AllOf(Args...args) {
	return (... && (args % 2 == 0)) ;
}

//We can also use a callable (in this case a lambda below)
template<typename...Args, typename Predicate>
bool AnyOf2(Predicate p, Args...args) {
	return (... || p(args)) ;
}
int main() {
	auto result = Sum3(1,2,3,4,5) ;
	//std::cout << result << std::endl;

	std::cout << std::boolalpha ;
	std::cout << "Any even?" << AnyOf(10,3,5) << std::endl; 
	std::cout << "All even?" << AllOf(10,30,52) << std::endl;

    std::cout << "Any even?" << AnyOf2([](int x){return x % 2 == 0;},10,3,5) << std::endl; 

}
