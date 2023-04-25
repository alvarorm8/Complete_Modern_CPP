
#include <iostream>
#include <string>
#include <type_traits>

/*
* C++17 feature added that allows the condition of an if to be evaluated at compile time.
* It discards branches of an if statement at compile time.
* 
* Syntax:
* 
* if constexpr(condition)
* 
* The expression condition must be a constant condition and it should be possible to be evaluated at compile time.
* 
* It can be used with template and non-template functions.
* 
* Only the block that follow the true condition is evaluated, the else blocks become discarded statements, but those
* must still be valid statements.
* 
* It also works with initialization inside if constexpr and runtime if statements.
* 
* If constexpr can be used only inside functions.
*/

/*
* Here with normal ifs, it would fail at compile time because the type traits are evaluated at runtime, 
* so if we try to pass a normal integer (for example), it would fail at compilation because we can't dereference it. 
* 
* With if constexpr, as it is evaluated at compile time, it compiles and works perfectly. Note that the code inside 
* if constexpr block should be valid even if the block is discarded.
*/
template<typename T>
void Print(const T& value) {
	if constexpr (std::is_pointer_v<T>) {
		std::cout << *value << std::endl;
	}
	else if constexpr(std::is_array_v<T>) {
		for (auto v : value) {
			std::cout << v << ' ';
		}
	}
	else {
		std::cout << value << std::endl;
	}
}

template<typename T>
std::string ToString(T value) {
	if constexpr (std::is_arithmetic_v<T>){
		return std::to_string(value) ;
	}else {
		return std::string{value} ;
	}
}

//Here using if constexpr the other blocks are discarded, so the generated code is simplier
void CheckMode() {
	if constexpr (sizeof(void *) == 4) {
		std::cout << "32-bit\n" ;
	}else if constexpr (sizeof(void *) == 8) {
		std::cout << "64-bit\n" ;
	}else {
		std::cout << "Unknown mode\n" ;
	}
}
int main() {
	CheckMode() ;
	
	/*int value{ 5 };
	auto s = ToString(value) ;
	Print(s) ;*/
	
	/*Print(&value);
	int arr[] = { 1,2,3,4,5 };
	Print(arr);*/
}