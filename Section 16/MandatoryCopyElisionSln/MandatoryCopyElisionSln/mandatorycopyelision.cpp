#include <iostream>
#define DELETE_COPY_MOVE
/*
* Before C++17, copy ellision was not mandatory.
* Since C++17 it is mandatory, so copies of temporary objects are avoided, it is mandatory for expressions where you are initializing an Lvalue with an Rvalue, which are, for example:
* - In copy initialization: item 2 we are initializing an Lvalue (n1) with an Rvalue (3)
* - Passing by value to a function: item 3
* - Returning a temporary by value in a function: item 1 and 4
* 
* When we use C++14 configuration, items 1,2,3 and 4 fails compilation since we have eliminated Copy and Move constructors in Number class.
* When we use C++17, even if we delete Copy and Move constructors, it still works
* 
* If the Create() function is implemented with the possibility commented, copy ellision won't be mandatory, since it is an Lvalue, not a temporary.
*/
class Number {
public:
	Number(int value) {
		std::cout << "Parameterized ctor\n" ;
	}
#ifdef DELETE_COPY_MOVE
	Number(const Number &) = delete ;
	Number(Number &&) = delete ;
#else
	//Without copy constructor and move constructor, copy ellision does not work
	Number(const Number &) {
		std::cout << "Copy ctor\n" ;
	}
	Number(Number &&){
		std::cout << "Move ctor\n" ;
	}
#endif
};

void Foo(Number n) {
	
} 

Number Create() {
	//One possible way copy ellision works
	//Number n{0} ;
	//return n ;

	//Second possible way copy ellision works
	return Number{0} ; // 1
}

/*
* Here, C++14 also will fail since there aren't copy or move constructors.
*/
template<typename T, typename...Args>
T Create(Args&&...args) {
	return T{args...} ;
}
int main() {
	//Number n1 = 3; -> expands to: Number n1 = Number{3} ; // 2
	//Foo(3) -> expands to: Foo(Number{3}) ; // 3

	//auto n2 = Create() ; // 4

	auto n3 = Create<Number>(0) ;
}

