#include <iostream>
#include <string_view>
/*
* C++17 introduces string_view, which allows us to deal with character sequences without allocating memory.
* Can be considered as a reference to a character sequence, but you can't modify the sequence.
* It stores a pointer to the string and the length, so it's fast and cheap to copy, but it should be used
* carefully since it can lead to bugs.
* The sequence it points to may not be null terminated (with \0), so it may not work with C string functions.
* 
* The advantage of string_view is that it can be used with all sequence characters, like QString from Qt
*/
#pragma region Example 1+
//In PrettyPrint since we are not modifying the message, we can use a string_view instead of a std::string
//which will create a copy of the string passed, so more memory will be occupied. If we use string_view, 
//no memory will be allocated
void PrettyPrint(std::string_view message, char ch) {
	for(int x = 0 ; x < message.length() ; ++x) {
		std::cout << ch ;
	}
	std::cout <<'\n' ;
	std::cout << message << '\n' ;
}
#pragma endregion

#pragma region Example 2
/*
* Here name can't be replaced since we are modifying it, but last can be replaced.
*/
enum class Title{MR, MRS, MS};
std::string & CombineName( std::string &name, std::string_view last, Title s) {
	switch (s) {
	case Title::MR:
		name.insert(0, "Mr.") ;
		break ;
	case Title::MRS:
		name.insert(0, "Mrs.") ;
		break ;
	case Title::MS:
		name.insert(0, "Ms.") ;
		break ;
	}
	return name += last ;
}
#pragma endregion
/*
* In Person class, we can't replace m_Name type with a string_view, since if a temporary is passed to 
* the constructor, the temporary will be destroyed, and m_Name will be dangling, pointing to an invalid
* direction.
*/
#pragma region Example 3
class Person {
	std::string m_Name;
public:
	Person(std::string name):m_Name{std::move(name)} { //Don't use string view in constructor neither, better to move
		
	}
	void Print()const {
		std::cout << m_Name << std::endl; 
	}
};

Person CreatePerson(std::string_view name) {
	std::string n{name} ;
	Person p{n} ;
	return p ;
}
void WithClass() {
	using namespace std::string_literals ;
	//std::string n{} ;
	Person p{"Umar"} ;
	
	p.Print() ;
}
#pragma endregion

void BasicUsage() ;

int main() {
	//PrettyPrint("Hello world", '#') ;
	WithClass() ;
}

void BasicUsage() {
	//These are only examples, there are more functions like front(), back(), MaxSize()... it supports iterators and provides comparison operators with other string views
	using namespace std::string_view_literals ;
	std::string_view sv1 = "Hello world" ;

	std::string str1{"Hello"} ;
	std::string_view sv2 = str1 ;

	auto sv3 = "Using\0literals"sv ;

	std::cout << "Size:" << sv3.length() << std::endl;
	std::cout << sv3 << std::endl;

	//may return nullptr or a pointer to a sequence with embebed null characters (\0) or may not have null termination
	//for example, when printing data with sv3, it only prints Using since it has a \0
	std::cout << "data()" << sv3.data() << std::endl; 

	//Access to characters
	std::cout << sv3[0] << std::endl; //undefined behaviour if index is wrong
	std::cout << sv3.at(0) << std::endl ; //throws out of range exception if index is wrong

	auto f = sv3.find("literals") ; //returns the index of the first occurrence
	if(f != std::string::npos) {
		std::cout << "Found at index:" << f << std::endl ;
	}

	sv3.remove_prefix(3) ; //removes the first 3 characters from the string view, but the string it points to still the same
	std::cout << sv3 << std::endl ;

	sv3.remove_suffix(2) ; //removes the last 2 characters from the string view, but the string it points to still the same
	std::cout << sv3 << std::endl ;

	auto sv4 = sv1.substr(0, 5) ; //Gets a new string view starting at 0 with length 5

	// Here if we use data() to print it would give the entire Hello World, since it is the data it points to.
	// That's why we don't have to use data() to print the value
	std::cout << sv4 << std::endl; 
}