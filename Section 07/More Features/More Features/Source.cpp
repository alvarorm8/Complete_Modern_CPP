#include <cstdlib>
#include <iostream>
#include <memory>
#pragma region Deleters
/*
* -------------------------------------Deleter-------------------------------------
* Smart pointers always call a deleter when the finished their execution, this deleter is in charge of freeing the resources 
* the smart pointer points to. By default, the call the function delete, which frees the resources adquired with new. But in some
* cases we may have not adquired the resources with new. For example, we can adquire them with malloc, or adquire a different type 
* of object which requires other function. 
* 
* We can specify the smart pointer, which deleter has to call when it finishes its execution. I can pass any kind of callable, like a
* global function, a lambda expression, etc.
* 
* I have to pass the type of deleter: a function, a class, a structure, etc., and then the deleter. For example in function UniquePtrDeleters
* we can pass the type Free and a temporary object, we can pass a permanent object too:
* 
* std::unique_ptr<int, Free> p {(int*) malloc(4), Free{}} ;
* 
* Or if we do it with a function, we specify the type of the function pointer and the address of the function:
* 
* std::unique_ptr<int, void (*)(int *)> p {(int*) malloc(4), MallocFree} ; 
* 
* The first (*) indicates it's a function pointer, then comes the function parameter type. MallocFree is the address of the function.
* 
* It's recommended to use objects, like Free, since the size of the pointer is smaller.
* 
* For shared pointers we don't have to pass the type of deleter, simply the deleter in the constructor.
* 
* std::shared_ptr<int> p {(int*) malloc(4), Free{}};
* std::shared_ptr<int> p {(int*) malloc(4), MallocFree} ;
* 
* -------------------------------------Arrays in smart pointers-------------------------------------
* 
* If we define an array in a smart pointer, we have to define the type of variable as a array.
* 
* std::unique_ptr<int[]> p{new int[5]{1,2,3,4,5}} ;
* 
* If we don't define it like this, then the deleter will call delete instead of delete[]. 
* This can be done thanks to the type specialization of templates, which will be seen later.
* 
* With this, we can access members as an array: p[0] = 10 ;
* 
* The same was added to shared pointers in C++17, before, it was not possible to do it.
* 
* -------------------------------------Make functions-------------------------------------
* 
* Use of new and delete manually is discouraged in modern C++. To allocate resources, smart pointers 
* provide global functions through which you can construct a smart pointer without manually allocation.
* Those functions are called Make functions and they act as factory functions because they create an instance
* of a class.
* 
* For example, to create a unique pointer: auto p = std::make_unique<int>(5) ; 
* For example, to create a shared pointer: auto p = std::make_shared<int>(5) ;
* 
* We can pass classes, arrays, etc. Examples are shown in main function.
* 
* NOTE: make_shared for arrays was added in C++20
* 
* The main disadvantage of these functions, is that you can not pass the deleter, it will be the default deleter, 
* so if you have to use a custom deleter, you have to create the smart pointer manually
*/
struct Free { //we can use a class too, but we want it to be public, that's why we use Struct
	void operator()(int *p) { //it receives the same type of pointer we have to release
		free(p) ;
		std::cout << "pointer freed\n" ;
	}
};
void MallocFree(int* p) {
	free(p);
	std::cout << "pointer freed\n";
}
void UniquePtrDeleters() {
	//I
	//std::unique_ptr<int, Free> p {(int*) malloc(4), Free{}} ;
	std::unique_ptr<int, void (*)(int *)> p {(int*) malloc(4), MallocFree} ;
	*p = 100 ;
	std::cout << *p << '\n' ;
	//free(p) ;
}

void SharedPtrDeleters() {
	std::shared_ptr<int> p {(int*) malloc(4), Free{}} ;
	//std::shared_ptr<int> p {(int*) malloc(4), MallocFree} ;
	*p = 100 ;
	std::cout << *p << '\n' ;
	//free(p) ;
}
#pragma endregion

void DynArray() {
	//std::unique_ptr<int[]> p{new int[5]{1,2,3,4,5}} ;

	//Support added in C++17 for shared_ptr
	std::shared_ptr<int[]> p{new int[5]{1,2,3,4,5}} ;
	p[0] = 10 ;
}

class Point {
public:
	Point(int x,int y) {
		
	}
};
int main() {
	//std::unique_ptr<int> p{new int{5}} ;
	{
		auto p = std::make_unique<int>(5) ;
		auto pt = std::make_unique<Point>(3,5) ;

		auto pArr = std::make_unique<int[]>(5) ; 
		//you can not initialize the array, but we can initialize them manually
		pArr[0] = 0 ;
	}

	{
		auto p = std::make_shared<int>(5) ;
		auto pt = std::make_shared<Point>(3,5) ;

		auto pArr = std::make_shared<int[]>(5) ;
		pArr[0] = 0 ;
	}
	
}