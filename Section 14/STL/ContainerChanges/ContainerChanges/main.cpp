#include <deque>
#include "Integer.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <set>

/*
* New features were added in C++11, which we'll see in this solution
*/

void Emplace() {
	std::vector<Integer> vInt ;
	//vInt.push_back(5) ; two objects are constructed, the one as an argument and a move constructor to store in the vector
	//vInt.emplace_back(5); only one object is created, the one stored in the vector. 

	///Emplace is a variadic template, so if the constructor accepts more than one argument, you can specify directly, for example:
	//vInt.emplace_back(5, "Hola", 6.76f) ;
	//There are also emplace_front and emplace, but not for all container, for example, emplace_front is not for vectors

	//If you have already an object, like val, there will be no difference between push_back and emplace_back
	Integer val{5} ;
	//vInt.push_back(val) ;
	vInt.emplace_back(val) ;

	std::vector<std::pair<int, std::string>> data ;
	data.push_back(std::pair<int, std::string>{100, "C++"}) ;

	data.emplace_back(100, "C++") ; //easier and creates only the object directly inside
}
void Shrink() {
	/*
	* when we insert new members in a container, sometimes memory must be reallocated to fit the new members
	* inserted. By default it uses copy constructor internally, but if we mark our move operations (constructor and assignment) 
	* with noexcept keyword, it will use move operations, but we have to be sure that no exception will be thrown.
	*/
	std::vector<int> vInt ;
	for(size_t i = 0 ; i < 100 ; ++i) {
		vInt.emplace_back(i) ;
	}
	std::cout << "Size:" << vInt.size() << '\n' ;
	std::cout << "Capacity:" << vInt.capacity() << '\n' ;
	vInt.erase(vInt.begin(), vInt.end()-10) ; //erase removes elements from the vector but not its capacity
	std::cout <<"After erase & shrink_to_fit\n" ;
	vInt.shrink_to_fit() ;//shrink removes capacity of the vector freeing memory not used. This is used to don't waste memory unnecessarilly
	std::cout << "Size:" << vInt.size() << '\n' ;
	std::cout << "Capacity:" << vInt.capacity() << '\n' ;
}
void VectorFunctions() {
	std::ifstream input{"main.cpp"} ;
	if(!input) {
		std::cout << "Could not open file\n" ;
		return ;
	}

	//with file_size we know the memory the file read will occupy
	auto size = std::filesystem::file_size("main.cpp") ;
	//std::vector<char> buffer ;
	std::string buffer ;
	buffer.resize(size) ;
	//char * buff = new char[size]{};
	input.read(buffer.data(), size) ;
	std::cout << buffer.data() << '\n' ;
	//delete []buff ;
}

template<typename Container>
void Print(const Container &cont, const char *msg="") {
	std::cout << msg << '\n' ;
	for(auto a : cont) {
		std::cout << a << '\n' ;
	}
}
void Erase() {
	//Now brace list initialization is allowed (with {})
	std::vector<int> vInt{1,2,3,4,2} ;
	std::list<int> lstInt{1,2,3,4,2} ;
	std::deque<int> deqInt{1,2,3,4,2} ;

	//With std::erase (C++20) we can remove an element by its value on any of the containers instanciated
	//Before, in vectors we can only remove based on position, in lists we have remove based on position, 
	//but with std::erase it's easier.
	std::erase(vInt,2) ;
	std::erase(lstInt,2) ;
	std::erase(deqInt,2) ;

	Print(vInt, "vector") ;
	Print(lstInt, "list") ;
	Print(deqInt, "deque") ;
}

int main() {
	//Changes on associative containers
	
	std::set<int> data{1,2,6,3} ;
	data.emplace_hint(data.begin(),0) ; //emplace_hint allows to insert the element as close as possible to the position of the iterator (it is also a variadic template as shown before)
	auto it0 = data.find(6) ; //before C++20 we use find
	if(it0 != data.end()) {
		std::cout << "Found\n" ;
	}
	auto found = data.contains(6) ; //after C++20 contains was added
	if(found){
		std::cout << "Found\n" ;
	}

	std::set<std::string> names{"Omar", "Ayaan", "Raihaan"} ;
	auto it = names.find("Omar") ; //this iterator is constant, so we can't update the value with it, we can only update through copy
	auto name = *it ; //only works if the type is copiable
	name[0] = 'U' ;
	names.erase(it) ;
	names.insert(name) ;

	//C++17 introduced extract, which returns the node in the tree of the element: set, multiset, map, multimap, unordered... all associative containers
	auto node = names.extract(it) ;
	node.value()[0] = 'U' ;//we can update through value function
	names.insert(std::move(node)) ;//move the node back into set, non-copiable, so we have to move it
	
	return 0;
}
