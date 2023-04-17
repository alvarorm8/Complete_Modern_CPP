#include <iostream>
/*
* Continuation of the solution Function Pointers
* 
* Function object: is an object of a class or struct that has the function call operator overloaded.
* Like, for example, Comp2. They are more frequently implemented like structs rather than classes.
* 
* There's a great difference between a function pointer and a function object, which is that the function
* object is not a global function, whose limitation were highlighted in the previous solution. 
* 
* This makes function object to have advantages over function pointers:
* 1. It is possible for the compiler to know which function has to call, so it's possible to optimize it. It can be faster.
* 2. It can have a state, not like function pointers which can not.
* 
* In this case, in the function Sort, we substitute the function pointer in the function with a template parameter, which
* can be both, a function pointer and a function object.
* 
*/
//using Comparator = bool(*)(int, int);
template<typename T, int size, typename Comparator>
void Sort(T(&arr)[size], Comparator comp) {
	for (int i = 0; i < size-1; ++i) {
		for (int j = 0; j < size - 1; ++j) {
			if (comp(arr[j], arr[j + 1])) {
				T temp = std::move(arr[j]);
				arr[j] = std::move(arr[j + 1]);
				arr[j + 1] = std::move(temp);
			}
		}
	}
}
//Function pointers as comparators
bool Comp(int x, int y) {
	return x > y;
}
bool Comp1(int x, int y) {
	return x < y;
}


//Function Object as comparator
struct Comp2 {
	bool operator()(int x, int y) {
		return x > y;
	}
};
int main() {
	Comp(3, 5);
	Comp2 comp;
	comp(3, 5);// it is like doing comp.operator()(3,5) ;
	int arr[]{ 1,6,8,4,0 };
	for (auto x : arr) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	Sort(arr, comp); // Call with function object
	//Sort(arr, Comp1); // Call with function pointer
	for (auto x : arr) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	return 0;
}