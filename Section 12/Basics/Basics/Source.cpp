#include <iostream>
#include "Assignment1.h"
#include "Assignment3.h"
//Old Code
//int Max(int x, int y) {
//	return x > y ? x : y;
//}
//float Max(float x, float y) {
//	return x > y ? x : y;
//}

/*
* We can also use the name class instead of typename, at this level it makes no difference.
* Differences are only seen at advanced template programming.
* 
* The compiler will generate an instance for each function call depending on the arguments type. If the function is not called
* in the code, the compiler won't generate any instance.
*/

//Primary Template
template<typename T>
T Max(T x, T y) {
	std::cout << typeid(T).name() << std::endl;
	return x > y ? x : y;
}

//Explicit Instantiation of Max for char type to force the compiler to generate this instance of the function.
template char Max(char x, char y);

//Explicit Specialization for Char types

//In const char * types, the normal definition is not correct, so we specilize the function for const char * types.
//Specializations must be defined in .cpp files, not in .h files because it would declare 2 times the same
//function causing a bug.
//For a specialization to exist, the general definition of the template must exist.

template<> const char * Max<const char*>(const char *x, const char *y) {
	std::cout << "Max<const char*>()" << std::endl;
	return strcmp(x, y) > 0 ? x : y;
}

void Examples() {
#pragma region Instantiation Examples
	Max(static_cast<float>(3), 5.5f);

	//Override compiler's deduction process
	Max<double>(3, 6.2);

	//Causes implicit instantiation of Max<int>
	int(*pfn)(int, int) = Max;

#pragma endregion
#pragma region Explicit Instantiation
	const char *b{ "B" };
	const char *a{ "A" };
	auto s = Max(a, b);
	std::cout << s << std::endl;
#pragma endregion
}

/*
Non-type template parameter

This type of arguments are more common in classes.

The parameter passed is constant, we can't pass a variable to Print
Constants can be: addresses, references, integrals, nullptr, enums, etc.
 
Error: int x = 10; Print<x>();
No error: int x = 10; Print<sizeof(x)>()
No error: Print<30>();
*/
template<int size>
void Print() {
	char buffer[size];
	std::cout << size << std::endl;
}
//Requires size as explicit argument
template<typename T>
T Sum(T*parr, int size){
	T sum{};
	for (int i = 0; i < size; ++i) {
		sum += arr[i];
	}
	return sum;
}
//Size is implicitly calculated in non-type template argument
//The argument to the function is a reference to an array
template<typename T,int size>
T Sum(T (&arr)[size]) {
	T sum{};
	for (int i = 0; i < size; ++i) {
		sum += arr[i];
	}
	return sum;
}
int main() {
	const int* x = new int[] {1, 2, 3, 4, 5, 6, -20, -24};
	std::cout << "Assignment1::Max: " << Assignment1::Max(x, 8) << std::endl;
	std::pair<int, int> pair = Assignment1::MinMax(x, 8);
	std::cout << "Assignment1::MinMax: (" << pair.first << ", " << pair.second << ")" << std::endl;
	Print<3>();
	int arr[]{ 3,1,9,7 };
	//int (&ref)[4] = arr ; //reference to arr, if we put a wrong size it gives a compilation error
	int sum = Sum(arr);
	std::cout << sum << std::endl; 

	int x1[]{1, 2, 3, 4, 5, 6, -20, -24};
	std::cout << "Assignment3::Max: " << Assignment3::Max(x1) << std::endl;
	std::pair<int, int> pair1 = Assignment3::MinMax(x1);
	std::cout << "Assignment3::MinMax: (" << pair.first << ", " << pair.second << ")" << std::endl;
	delete[] x;
	return 0;
}