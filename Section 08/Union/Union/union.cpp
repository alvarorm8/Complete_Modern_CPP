#include <iostream>
#include <string>
/*
* A union is similar to a structure, but all elements share the same address, so the union takes less memory. The disadvantage is
* that if we set the value to an element, the rest of the element will have wrong information if we try to access them.
* 
* The size of the union is the size of the largest element inside it. 
* 
* In C++ unions can have constructors and destructors, but we can only initialize only 1 member, for example x or ch in Test
* 
* If the union has user defined objects with default constructors, the union has not a default constructor and destructor,
* so we have to write it manually, like in UDT. 
* 
* We have to initialize manually the objects inside the union, like a and b in UDT. We do it with the placement new operator, 
* which does not allocate memory, only initializes it, since in the union, memory has alreay been allocated:
* 
* new (address to create the object) object
* 
* For example:
* 
* new(&udt.s) std::string{"Hello world"} ;
* 
* And also, we have to manually destroy the objects. For example for object a in udt:
* 
* new (&udt.a) A{} ;
* udt.a.~A() ;
*/
union Test {
	int x ;
	char ch ;
	double d ;
	Test(): ch{'a'} {
		std::cout << __FUNCSIG__ << std::endl; 
	}
	~Test() {
		std::cout << __FUNCSIG__ << std::endl; 
	}
};
struct A {
	A() {
		std::cout << __FUNCSIG__ << std::endl;
	}
	~A() {
		std::cout << __FUNCSIG__ << std::endl;
	}

	A(const A& other) {
		std::cout << __FUNCSIG__ << std::endl;
	}

	A(A&& other) noexcept{
		std::cout << __FUNCSIG__ << std::endl;
	}

	A& operator=(const A& other) {
		std::cout << __FUNCSIG__ << std::endl;
		if (this == &other)
			return *this;
		return *this;
	}

	A& operator=(A&& other) noexcept {
		std::cout << __FUNCSIG__ << std::endl;
		if (this == &other)
			return *this;
		return *this;
	}
};
struct B {

	B() {
		std::cout << __FUNCSIG__ << std::endl;

	}
	~B() {
		std::cout << __FUNCSIG__ << std::endl;

	}

	B(const B& other) {
		std::cout << __FUNCSIG__ << std::endl ;
	}

	B(B&& other) noexcept {
		std::cout << __FUNCSIG__ << std::endl ;
	}

	B& operator=(const B& other) {
		std::cout << __FUNCSIG__ << std::endl ;
		if (this == &other)
			return *this;
		return *this;
	}

	B& operator=(B&& other) noexcept {
		std::cout << __FUNCSIG__ << std::endl ;
		if (this == &other)
			return *this;
		return *this;
	}
	virtual void Foo(){}
	
};

union UDT {
	A a ;
	B b ;
	std::string s ;
	UDT() {
		
	}
	~UDT() {
		
	}
};
int main() {
	using namespace std::string_literals ;
	UDT udt ;
	//new(&udt.s) std::string{"Hello world"} ;

	new (&udt.a) A{} ;
	udt.a.~A() ;
	
	/*std::cout << sizeof(Test) << std::endl; 
	Test t ;
	std::cout << t.ch << std::endl;

	t.x = 1000 ;

	std::cout << t.ch << std::endl; */
	
}