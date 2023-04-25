#include <iostream>
#include <map>

/*
* Structure bindings allows initialization of multiple variables with elements or members of an object, which can be an object of a class/structure or an array.
* For object classes, the members should be public.
* The number of variables should match the number of elements in the object.
* An anonymous entity is created.
* 
* auto [variables] = object;
* <cv qualifiers> auto &[variables] = object; (const, volatile qualifiers)
*/

struct Person {
	std::string m_Name ;
	int m_Age ;
	Person() = default ;
	Person(const std::string &name, int age):m_Name{name}, m_Age{age}{}
};

struct S1 {
	int arr1[8] ;
	char ch1[256] ;
};

int main() {
	Person p{"Ayaan", 14} ;
	/*auto name = p.m_Name ;
	auto age = p.m_Age ;*/

	//auto [name, age] = p ; //copy variables. Here the anonymous entity is a copy of p
	const auto &[name, age] = p ; //Here the anonymous entity is a reference of p, so the changes in its variables is reflected in p variables (if const is not present).
	//age = 10 ; //As const is applied, we can't modify the value

	std::cout << p.m_Age << std::endl;

	std::pair<int,int> p1{3,5} ;
	auto [key, value] = p1 ;

	std::map<int, std::string> errorInfo{ {1, "Not available"}, {2, "Port is in use"}} ;

	for(auto err : errorInfo) {
		std::cout << err.first << ":" << err.second << std::endl; 
	}

	for(auto [key, value] : errorInfo) {
		std::cout << key << ":" << value << std::endl; 
	}

	int arr[] = {1,2,3} ;
	auto [a, b, c] = arr ;//separate elements of the array

	auto arr2 = arr ; //arr2 is a pointer, not an array. arr decays to a pointer.
	
	S1 s{};
	auto [s1, s2] = s; //s1 and s2 are arrays since they're in a struct or a class
}