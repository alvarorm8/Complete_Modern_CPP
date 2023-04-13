#include <iostream>
#include "Integer.h"
#include "Assignment4.h"

#include <tuple>
#include <functional>

/*
* Variadic templates can be simplified with C++17 fold expressions.
* 
* Variadic templates are functions and classes that accept an arbitrary number of arguments. These can be of any type, not all
* have to be of the same type.
* 
* If we want to use an initializer_list, the arguments have to be of the same type.
* 
* To access the elements of the argument list, we have to use recursive calls to the function. In each call the number of arguments will 
* be reduced by 1. We have to provide a base case function to stop the recursion. In this case Print() is the base case function.
* 
* The calls are done like this in the following call Print(1,2.5,3,"4");:
* 
* 1. Print(1, 2.5, 3, "4") ;
* 2. Print(2.5, 3, "4") ;
* 3. Print(3, "4") ;
* 4. Print("4") ;
* 5. Print() ;
* 
* When it reaches line 5, the recursive call is stopped.
* 
* Important: the argument list will be expanded by the compiler depending on the values passed. So for example, if we pass Print(1, 2.5, 3, "4"), those
* will be expanded to (int, double, int, const char *). If we have a class which constructor accepts a list of elements (like in Assignment4.h), we can pass
* the argument list directly to the constructor, and that's the solution to Assignment4.
* 
* If we try to pass a wrong parameter to the constructor, the compiler will fail, like in p2 pointer.
*/
//Works only for homogenous data types
//template<typename T>
//void Print(std::initializer_list<T> args) {
//	for (const auto &x : args) {
//		std::cout << x << " ";
//	}
//}

void Print(){
	std::cout << "Basic Print" << std::endl;
}

//Template parameter pack, a normal one and variadic template.
template<typename T, typename...Params>
//Function parameter pack
void Print(T &&a, Params&&... args) {
	//We use rvalue as parameters and std::forward in this function to avoid copies of user defined objects, like Integer.
	//If we don't use std::forward the type will be lost with the recursive call.
	//We can know the number of parameters with any of the following 2 options:
	
	std::cout << "size: " << sizeof...(args) << std::endl;
	//std::cout << sizeof...(Params) << std::endl;
	std::cout << "element: " << a << std::endl;
	if (sizeof...(args) != 0) {
		std::cout << ",";
	}
	//We can forward a function parameter pack
	Print(std::forward<Params>(args)...);
}

int main() {
	//Print({ 1,2.5,3,4 });
	Print(1, 2.5, 3, "4");
	//Integer val{ 1 };
	//Print(0, val, Integer{ 2 });

	std::string * str = Assignment4::CreateObject<std::string>();
	std::cout << *str << std::endl;

	std::string* str2 = Assignment4::CreateObject<std::string>("String test");
	std::cout << *str2 << std::endl;

	int* p1 = Assignment4::CreateObject<int>();
	std::cout << *p1 << std::endl;

	Assignment4::Employee* emp = Assignment4::CreateObject<Assignment4::Employee>(
		"Bob",    //Name
		101,      //Id
		1000);   //Salary

	Assignment4::Contact* p = Assignment4::CreateObject<Assignment4::Contact>(
		"Joey",                //Name
		987654321,             //Phone number
		"Boulevard Road, Sgr", //Address
		"joey@poash.com");     //Email

	//Assignment4::Contact* p2 = Assignment4::CreateObject<Assignment4::Contact>(
	//	"Joey",                //Name
	//	987654321,             //Phone number
	//	"Boulevard Road, Sgr", //Address
	//	435);				   //Email

	emp->printClassInfo();
	p->printClassInfo();

	return 0;
}
