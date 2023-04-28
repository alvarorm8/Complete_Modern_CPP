#include <any>
#include <iostream>
/*
* C++17 provides a way of creating a variables that can store different types of variables.
* 
* Before, it was possible with the void*, but it is not typesafe, we can't know the type and 
* we need to manually manage the object's lifetime.
* 
* std::any is introduced which can store any variable of any type in a typesafe way.
* Contains the value and its type.
* The value is accessed through any_cast
* It will throw a bad_any_cast exception if you try to access a wrong type
*/
struct Number {
	int m_Num{} ;
	Number(int num): m_Num{num} {
		std::cout << __FUNCSIG__ << std::endl;
	}

	Number() {
		std::cout << __FUNCSIG__ << std::endl;
	}
	~Number() {
		std::cout << __FUNCSIG__ << std::endl;
	}

	Number(const Number& other) {
		m_Num = other.m_Num ;
		
		std::cout << __FUNCSIG__ << std::endl;
	}

	Number(Number&& other) noexcept {
		m_Num = other.m_Num ;
		other.m_Num = 0 ;
		std::cout << __FUNCSIG__ << std::endl;
	}

	Number& operator=(const Number& other) {
		std::cout << __FUNCSIG__ << std::endl;
		if (this == &other){
			return *this;
		}
		m_Num = other.m_Num ;
		
		return *this;
	}

	Number& operator=(Number&& other) noexcept {
		std::cout << __FUNCSIG__ << std::endl;
		if (this == &other)
			return *this;
		m_Num = other.m_Num ;
		other.m_Num = 0 ;
		
		return *this;
	}
		friend std::ostream& operator <<(std::ostream &out, const Number &n) {
		return out << n.m_Num ;
	}
};
void Basics() {
	std::any v1 = 5;
	//v1 = "Hello"s ;
	
	//As soon as we are finished with the object, we should call reset to free the possible memory allocated on the heap.
	v1.reset() ;
	if(v1.has_value()) { //check to access the value
		if(v1.type() == typeid(int)) {//check the type
			std::cout << std::any_cast<int>(v1) << std::endl; 
		}
	}
	try {
		std::cout << std::any_cast<std::string>(v1) << std::endl; 
	}catch(std::exception &ex) {
		std::cout << "Exception:" << ex.what() << std::endl; 
	}
}
int main() {
	using namespace std::string_literals ;
	//std::any number{Number{5}} ;//using a temporary
	auto n1 = std::make_any<Number>(5) ; //using make function
	//n1.reset() ;
	n1 = 5 ; //when we reassign the variable, the destructor of Number is called anyway, so in this case, no need to call reset

	//By default any_cast returns a copy, so the modification on n21 does not reflect to n1
	auto n21 = std::any_cast<int>(n1);
	n21 = 103;
	std::cout << std::any_cast<int>(n1) << std::endl;

	//Here we create a reference, so changes on n2 will be reflected in n1
	auto &n2 = std::any_cast<int&>(n1) ;
	n2 = 100 ;
	std::cout << std::any_cast<int>(n1) << std::endl ;

	//Here we create a pointer by passing the address of n1, so changes on p will be reflected in n1
	auto p = std::any_cast<int>(&n1) ;
	*p = 200 ;
	std::cout << *std::any_cast<int*>(p) << std::endl; 
	
}
