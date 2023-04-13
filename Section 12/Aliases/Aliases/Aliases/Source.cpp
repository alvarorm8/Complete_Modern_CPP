#include <iostream>
#include <vector>
#include <list>

/*
* Aliases are the same as typedefs but in a more natural way of writing them. It was introduced in C++11.
* 
* Another difference is that in aliases we can use templates, and in typedefs we can't.
* 
* For example:
* 
* template<typename T>
* using Names = std::vector<std::list<T>>;
* 
* Names<int> intNames;
* Names<std::string> stringNames;
*/

const char * GetErrorMessage(int errorNo) {
	return "Empty";
}

//We can see, alias is much easier to read than typedef
//typedef const char *(*PFN)(int);
using PFN = const char *(*)(int); // ShowError accepts a pointer function that accepts an int and returns a const char *
void ShowError(PFN pfn){
	
}
//typedef std::vector < std::list<std::string>> Names;

//template<typename T>
//using Names = std::vector<std::list<T>>;

using Names = std::vector<std::list<std::string>>;

int main() {
	Names names;
	Names nnames;

	PFN pfn = GetErrorMessage;
	ShowError(pfn);
	return 0;
}
