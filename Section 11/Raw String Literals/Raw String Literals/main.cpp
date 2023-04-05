#include <iostream>
#include <string>

/*
* C++11 Raw String Literal: used to prevent the necessity of things like \\ to print a \. They begin with R"()"
* We can create our own delimiter, it has to be shorter than 16 elements and composed as an array of characters, 
* it should not contain white spaces or \. For example:
* 
* std::string str2{ R"MSG()MSG" };
*/
int main() {
	std::string str{R"(C:\temp\newfile.txt)"};
	std::cout << str << std::endl;
	std::string str2{ R"MSG(C++ introduced filesystem API (in C++17).)MSG" };
	std::cout << str2 << std::endl;
	return 0;
}