#include <iostream>
#include "Integer.h"
class Product {
	Integer m_Id;
	int x;
public:
	/*
	* If you initialize the members inside the constructor, it is made through assignment
	* It is better to do it through the Member Initialization List, which initializes the variables
	* through Initialization. The order has to be the same in which the members has been defined.
	*/
	Product(const Integer& id) :m_Id{ id }, x{id.GetValue()} /*Memeber Initialization List*/ {
		std::cout << "Product(const Integer &)" << std::endl;
		//m_id = id;
	}
	~Product() {
		std::cout << "~";
	}
	const Integer& GetInteger()const {
		return m_Id;
	}
	operator Integer() {
		return m_Id;
	}
};

int main() {
	// Initialization (prefered over assignment due to fewer calls to constructors)
	Integer a = 5;

	// Assignment 
	a = 19;




	return 0;
}