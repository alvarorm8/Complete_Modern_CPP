#include <iostream>
#include <set>
#include <functional> //greater, less
#include <map>
#include <string>
void Set() {
	/*
	* set, multiset
	* Implemented as binary tree
	* Elements are sorted with operators < > and based on the value
	* Value acts as key
	* Fast search
	* No random access
	* Elements can not be modified directly
	* Cannot be resorted
	* 
	* Efficient for search of elements, not so much for insertion or deletion
	*/
	std::multiset<int, std::greater<int>> s{ 8,2,0,9,5 }; //By default, the comparator is less
	//No push_back, only insert as elements are ordered automatically
	s.insert(1);

	//Only multiset allows duplicates
	s.insert(3);
	s.insert(3);
	s.insert(3);

	//Iterators are constant, so we can not modify the value
	auto itr = s.begin();
	//*itr = 3;
	while (itr != s.end()) {
		std::cout << *itr++ << " ";
	}
	std::cout << std::endl;

	//Erase by key or position
	s.erase(0); //based on the value (key)
	s.erase(s.begin()); //based on position
	itr = s.find(9); //returns the first occurence of the value passed
	if (itr != s.end()) {
		std::cout << "Element found" << std::endl; 
	}
	else {
		std::cout << "Not found" << std::endl;
	}
	//equal_range returns a pair. The first element is the first occurence and the second the 
	//first occurence greater than the key searched . If no occurence is found, the elements are the end operator
	auto found = s.equal_range(3); 
	while (found.first != found.second) {
		std::cout << *found.first++ << " ";
	}

	//Range based loop is also supported
	for (int i : s) {
		std::cout << i << std::endl;
	}
}
void Map() {
	/*
	* Implemented as binary tree
	* Stores a pair that contains a key and value
	* Elements are stored in sorted order based on a key
	* Fast search
	* No random access
	* Keys can not be modified directly
	*/
	std::multimap<int, std::string> m{
		{1, "Superman"},
		{2, "Batman"},
		{3, "Green Lantern"}
	};
	//Duplicate elements can only be stored in multimap
	m.insert(std::pair<int, std::string>(8, "Aquaman"));
	m.insert(std::make_pair(6, "Wonder Woman"));
	m.insert(std::make_pair(6, "Powergirl"));

	//Only map support [] operator, not multimap
	/*m[0] = "Flash";
	m[0] = "Kid Flash";*/
	auto itr = m.begin();
	std::cout << itr->first << " : " << itr->second << std::endl; //first key, second value
	m.erase(0); //delete first element
	//returns a pair that contains begin & end of the range.
	auto found = m.equal_range(6); //only in multimap
	while (found.first != found.second) {
		std::cout << found.first->first << ":" << found.first->second << std::endl;
		found.first++;
	}

	//Avoid using [] for searching as it will insert an empty element if a key cannot be found
	//std::cout << "10:" << m[10] << std::endl;
	
	// Iterator with range based loop
	for (const auto &x : m) {
		std::cout << x.first << ":" << x.second << std::endl;
	}

	//Lookup by key
	itr = m.find(1);
	if (itr != m.end()) {
		std::cout << "Found: " << itr->second << std::endl;
	}
	else {
		std::cout << "Not found" << std::endl;
	}

}
int main() {
	Map();
	return 0;

}