
#include <iostream>
#include <type_traits>
/*
* Type traits give the ability to introspect, which is: find the characteristics of types at compile time and transform the properties of the type.
* 
* This is useful at template metaprogramming
* 
* They can return a boolean or a type.
* 
* std::is_reference<T>::value returns a boolean
* 
* std::remove_reference<T>::type returns a type
*/
template<typename T>
T Divide(T a, T b) {
	if(std::is_floating_point<T>::value == false) {
		std::cout << "Use floating point types only\n" ;
		return 0 ;
	}
	return a / b ;
}
template<typename T>
void Check(T &&) {
	std::cout << std::boolalpha ;
	std::cout << "Is reference?" << std::is_reference<T>::value << std::endl ;
	std::cout << "After removing:" << 
		std::is_reference<typename std::remove_reference<T>::type>::value << std::endl; 
}
int main() {
	Check(5) ;
	int value{} ;
	Check(value) ;
}