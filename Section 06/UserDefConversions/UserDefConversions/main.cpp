#include <iostream>
#include "Integer.h"
class Product{
	Integer m_Id ;
public:
	Product(const Integer &id):m_Id{id} {
		std::cout << "Product(const Integer &)" << std::endl; 
	}
	~Product(){
		std::cout << "~" ;
	}
	const Integer & GetInteger()const{
		return m_Id ;
	}
	operator Integer(){
		return m_Id ;
	}
};

int main() {

	/*
	* C style casts are discouraged in C++.That is because for several reasons :
	*	1. Does not check for validity of the casts (example below)
	*	2. Discards the qualifiers, for example const.
	* 
	* The types of casts in C++ are:
	*	1. static_cast: casts and check the validity of conversion
	*	2. reinterpret_cast: allows casts between any type of variables
	*	3. const_cast: 
	*	4. dynamic_cast
	*/

	//Basic casting

	int a = 2, b = 5;
	float f = a; // implicit cast
	float f = (float)a/b;// explicit cast to float in C-Style (discouraged since it does not check if the cast is valid or not)
	float f = static_cast<float>(a)/b; // It checks validity of the cast

	char * p1 = (char*)&a; //No check, but this is incorrect
	char * p2= static_cast<char*>(&a); // It checks validity of the cast, in this case, it fails because the types are not compatible

	const int c = 10;
	int* p3 = reinterpret_cast<int*>(&c); //Allows conversions between any type and keeps qualifiers, in this case it fails because of the qualifier
	int* p3 = const_cast<int*>(&c);

	// Primitive to user defined classes

	Integer obj{ 6 };
	Integer obj2 = 9; //implicit call to parametrized constructor, if it exists. If not, the compiler will give an error
	Print(3); //same as before, implicit call to parametrized constructor to convert 3 into a Integer object
	Print2(5); //same as before, implicit call to parametrized constructor to convert 5 into a Integer object

	obj = 7; //implicit call to assignment operator (in this case move operator since the value 7 is an rvalue), converts 7 into an Integer and then assigns it to obj.

	// User defined to primitive

	int x = obj; //use of the convert operator defined in Integer.h: operator int(), if it's not defined as explicit

	// User defined to user defined

	Product p{5} ;
	Integer id{10} ;
	Integer id2 = p.GetInteger(); //easy way to convert, but we want to do it without a method

	id = p ; // id = p.operator Integer() ; implicit call to type conversion operator

	if(id == p){ //implicit call to type conversion operator
		std::cout << "Id matches with the product\n" ;
	}

	if (p == id) { //it does not work since the operand on the left is not Integer type
		std::cout << "Id matches with the product\n";
	}

	return 0;
}

void Print(Integer a) {};
void Print2(const Integer &a) {};