
#include <iostream>
#include <optional>

/*
* C++17 new library type that can be used when a function may or not return a value.
* With std::optional, you don't have to compare with values like 0, nullptr, etc., since it can
* represent a type that may or not contain a value (nullable type)
* 
* To represent an empty value you can use std::nullopt, or default construct a std::optional. 
* 
* std::optional can be deep copied
* 
* You can not store references inside std::optional. 
* 
* If you try to access and it does not contain any value, it throws an std::bad_optional_access
* 
* With std::optional we can shave memory and make our code more efficient. This is seen in Contact 
* example below.
*/

const char * GetErrorString(int errorNo) {
	switch (errorNo) {
	case 0:
		return "Invalid input" ;
	case 1:
		return "Connection not established yet\n" ;
	default:
		return "" ;
	}
}
std::optional<const char *> GetErrorStringOp(int errorNo) {
	switch (errorNo) {
	case 0:
		return "Invalid input" ;
	case 1:
		return "Connection not established yet\n" ;
	default:
		return std::nullopt ;
	}
}
class ContactName {
	std::string first ;
	std::optional<std::string> middle ;
	std::string last ;

public:

	ContactName(const std::string& f, const std::optional<std::string>& m, const std::string& l)
		: first{f},
		  middle{m},
		  last{l} {
	}

	void Print() {
		std::cout << first << ' '  ;
		std::cout << middle.value_or("") << ' ' ;
		std::cout << last << '\n' ;
	}
};
int main() {
	////////////////////////// Creation of optional and checking the value //////////////////////////
	std::optional<int> value{ 5 };
	std::optional value2{ 5 }; //We can use compile time argument deduction
	auto value3 = std::make_optional(4); //We can use make functions
	if (value.has_value()) { //First way to check value
		std::cout << value.value() << std::endl; //First way to access the value
	}
	if (value) { //Second way to check value
		std::cout << *value << std::endl;//Second way to access the value
	}
	//value.value() is better, since it throws bad_optional_access if it's empty. Dereference (*value) on the other side, 
	//has an undefined behaviour

	value = 1; //Assign new value
	value.reset(); //-No value is inside

	////////////////////////// Use of Contact //////////////////////////

	auto f = strlen("") ;
	std::cout << f ;
	ContactName n1{"Umar", "Majid", "Lone"} ;
	ContactName n2{"Ayaan", std::nullopt, "Lone"} ;
	//Since in n2 there's no middle name and we're using optional, memory is saved. An empty string
	//would have allocated memory, so it's less efficient.

	n1.Print() ;
	n2.Print() ;

	////////////////////////// Use of GetErrorString //////////////////////////
	// In the first way, we have to check the value returned
	// In the second, we
	
	auto message = GetErrorString(1) ;
	if(strlen(message) != 0) {
		std::cout << message << std::endl; 
	}else {
		std::cout << "Unknown error number\n" ;
	}

	try{
	auto errorMessage = GetErrorStringOp(4) ;

	//Return contained value or the argument passed in value_or. 
	//The type passed to value_or must be the same inside optional
	std::cout << errorMessage.value_or("Default") << std::endl ;
	
	if(errorMessage.has_value()) {
		//Throws exception std::bad_optional_access if no value
		std::cout << errorMessage.value() << std::endl ;
	}else {
		std::cout << "Unknown error number\n" ;
	}

	errorMessage = GetErrorStringOp(4) ;
	
	if(errorMessage) {
		//Undefined behavior when no value exists in optional
		std::cout << *errorMessage << std::endl ;
	}else {
		std::cout << "Unknown error number\n" ;
	}
	}catch(std::exception &ex) {
		std::cout << "Exception:"<< ex.what() << std::endl ;
	}
	
}