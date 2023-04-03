#include <iostream>
#include <sstream>
/*
* Stringstreams are just like io streams, but instead of reading info from keyboard and/or program
* and displaying it to the console, stringstreams do the same but maintaining the info inside a string
* that they have internally. With this, we can for example write to a box in the GUI of the application.
* 
* There are 3 types:
* 
* std::stringstream ss ; //both insertion and extraction, write to it and read from it
* std::istringstream is ; //insertion, write to it
* std::ostringstream os ; //extraction, read from it
* 
* We can access the buffer with the function str().
*/

//Assignmet 2

//Two functions from assignment 1
std::string ToUpper(const std::string& str) {
	std::string result;
	for (int i = 0; i < str.length(); ++i) {
		result.append(1, toupper(str[i]));
	}
	return result;
}
std::string ToLower(const std::string& str) {
	std::string result;
	for (int i = 0; i < str.length(); ++i) {
		result.append(1, tolower(str[i]));
	}
	return result;
}

enum class Case { SENSITIVE, INSENSITIVE };

size_t Find(
	const std::string& source,         //Source string to be searched
	const std::string& search_string,  //The string to search for
	Case searchCase = Case::INSENSITIVE,//Choose case sensitive/insensitive search
	size_t offset = 0) {                //Start the search from this offset
		/*
		return position of the first character
		of the substring, else std::string::npos
		*/
	switch (searchCase) {
	case Case::SENSITIVE:
		return source.find(search_string, offset);
		break;
	default: //Case::INSENSITIVE
		std::stringstream ss_source(source);
		std::stringstream ss_search(search_string);
		ss_source.str(ToLower(ss_source.str()));
		ss_search.str(ToLower(ss_search.str()));
		return ss_source.str().find(ss_search.str(), offset);
		break;
	}
	return 0;
}

int main() {
	{
		int a{ 5 }, b{ 6 };
		int sum = a + b;
		std::stringstream ss;
		ss << "Sum of " << a << " & " << b << " is :" << sum << std::endl;
		std::string s = ss.str(); //get the string buffer
		std::cout << s << std::endl;
		ss.str(""); //assign internal string to ""
		std::cout << "ss.str(): " << ss.str() << std::endl;
		ss << sum;
		auto ssum = std::to_string(sum); //C++11 function that uses stringstreams to convert to string, there are for doubles, float, etc.
		std::cout << ssum << std::endl;
	}
	{
		std::string data = "12 89 21";
		int a;
		std::stringstream ss;
		std::stringstream ss2(data); //we can also initialize directly
		//ss2.write("hoola", 5);
		ss2 << "hoola";
		std::cout << "ss2.str(): " << ss2.str() << std::endl;
		//If we modify data inside ss2, data keeps the same
		std::cout << "data: " << data << std::endl;
		ss.str(data);
		while (ss >> a) {
			std::cout << a << std::endl;
		}
		//we can achieve the same with std::stoi
		int x = std::stoi("54"); //C++11 function that uses stringstreams to convert to string, there are for doubles, float, etc.
	}
	{
		//Assignment 2
		std::string source = "Hello my name is Alvaro Ramirez";
		std::string search = "ALvaro";
		auto position = Find(source, search, Case::SENSITIVE, 0);
		if (position != std::string::npos)
			std::cout << "String " + search + " found in " + source + " at position " << position << std::endl;
		else
			std::cout << "String " + search + " not found in " + source << std::endl;
	}
	return 0 ;
	
}