#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
/*
* Iterators are pointer like objects.
* We can access the elements by the position of the iterator.
* They overload operators like ++, --, *
* They are created through begin() and end() functions. 
* 
* The end iterator points to the next position of the last position of arrays, NOT to the last position, 
* so we should never dereference (*) the end iterator.
*/
void Array() {
	/*
	* Wraps C-style arrays, but supports iterators, knows its size, random access is supported, can be used in C functions and can not grow 
	*/
	std::array<int, 5> arr{ 3,1,8,5,9 }; //specify type and size
	for (int i = 0; i < arr.size(); ++i) {
		arr[i] = i;
	}
	auto itr = arr.begin(); //iterator
	while (itr != arr.end()) {
		std::cout << "iterator: " << *itr << std::endl;
		++itr;
	}
	for (auto x : arr) { //internally uses iterators
		std::cout << x << " ";
	}
	std::cout << std::endl; 
	arr.data(); //returns a pointer to the internall array, so it can be passes to C functions.
}
void Vector() {
	/*
	* Like an array but it can grow. It's not good for insertion/deletion but good for addition/removal at the end.
	*/
	std::vector<int> coll{ 1,2,3,4 }; //we can specify a second parameter as template, which is the allocator for memory management, but the default allocator is good for most cases
	for (int i = 0; i < 5; ++i) {
		coll.push_back(i * 10);
		std::cout << coll.size() << std::endl;
	}
	coll[0] = 100;
	//for (int i = 0; i< coll.size(); ++i) {
	//	std::cout << coll[i] << " ";
	//}
	auto itr = coll.begin();
	while (itr != coll.end()) {
		std::cout << *itr++ << " ";
	}
	coll.insert(coll.begin(), 700); //this makes all the elements to shift one position to fit the new one, so is bad in performance
	coll.erase(coll.end()-5);//same as insert, has to shift all the elements 
	coll.pop_back();//remove last element
}
void Deque() {
	/*
	* Double ended que. It's like a vector, but efficient for addition/removal at beginning and end. It's not good for insertion/deletion.
	*/
	std::deque<int> coll;
	//std::deque<int> coll{ 1,2,3,4 }; //also supported
	for (int i = 0; i < 5; ++i) {
		coll.push_back(i * 10);
	}
	for (int i = 0; i < 5; ++i) {
		coll.push_front(i * 10);
	}
	coll[0] = 100;
	//for (int i = 0; i< coll.size(); ++i) {
	//	std::cout << coll[i] << " ";
	//}
	auto itr = coll.begin();
	while (itr != coll.end()) {
		std::cout << *itr++ << " ";
	}
	coll.insert(coll.begin(), 700);
	coll.erase(coll.end() - 5);
	coll.pop_back();
	coll.pop_front();
}
void List() {
	/*
	* Implemented as a two-way linked list (each element has a pointer to the next and previous element)
	* Efficient for insertion/deletion anywhere
	* Does not provide random access
	*/
	std::list<int> coll;
	//std::list<int> coll{ 1,2,3,4 }; //also supported
	for (int i = 0; i < 5; ++i) {
		coll.push_back(i * 10);
		//coll.push_front(i * 10)
	}
	auto itr = coll.begin();
	while (itr != coll.end()) {
		std::cout << *itr++ << " ";
	}
	itr = coll.begin();
	coll.insert(itr, 800);
	coll.erase(itr);
}
void ForwardList() {
	/*
	* Like a List but requires less memory since it's only one direction.
	* Does not provide support for size
	* Elements are always added at the front, so when we read them, they are read in reverse order they were added
	*/
	std::forward_list<int> coll;
	//std::forward_list<int> coll{ 1,2,3,4 }; //also supported
	for (int i = 0; i < 10; ++i) {
		coll.push_front(i);
		//no push back
	}
	
	for (auto x : coll) {
		std::cout << x << " ";
	}
	coll.insert_after(coll.begin(), 10); //inserted at second position, since it only contains the direction of the next element
	coll.erase_after(coll.begin()); //erase the second position
}
int main() {
	std::cout << "////////////// Array function //////////////" << std::endl;
	Array();
	std::cout << "////////////// Vector function //////////////" << std::endl;
	Vector();
	std::cout << "////////////// Deque function //////////////" << std::endl;
	Deque();
	std::cout << "////////////// List function //////////////" << std::endl;
	List();
	std::cout << "////////////// Forward List function //////////////" << std::endl;
	ForwardList();
	return 0;
}