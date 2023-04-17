#include <iostream>

/*
* /////////////// Reference to array /////////////////////////
* 
* First, a reference to an array is used in functions which accepts an array with unspecified length, for example:
* 
void print(int arr[], size_t n) {
    for (int element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Declaring and initializing Integer array with custom input entries
    int a[]{ 1, 2, 3, 4 };
    size_t size = sizeof(a) / sizeof(a[0]);
    print(a, size);
}

* The compiler will print this error: 
*
* test.cpp: In function 'void print(int*, size_t)':
* test.cpp:5:21: error: 'begin' was not declared in this scope
      for(int element: arr){
* 
* Output Explanation:
* 
* Here it is clear that int* doesn’t have any information about the underlying array but if you pass an array by reference using the template the above code will work. 
* As reference array retains information about underlying array and its type would be int[4], not int*.
* 
* The syntax is the following: data_type (&name)[size] = array; 
* 
template<int size>
void print(int(&arr)[size]) {
    for (int element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    int a[]{ 1, 2, 3, 4 };
    print(a);
}

* This function will work as it accepts a reference to an array.
*/

template<int size>
void print(int(&arr)[size]) {
    for (int element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

/*
* /////////////// Function pointers and callbacks /////////////////////////
* 
* A function pointer is a generic object which represents the address of a function type.
* It can be the address of an specific function or a parameter of another function.
* If it's the parameter to another function, when we want to use the function we have to implement that function 
* parameter. This is usefull since we can specialize a specific part of a function without specializing the full
* function. 
* 
* The syntax is the following:
* 
* Declaring
* return_type (*FuncPtr) (parameter type, ....); 
* 
* Referencing
* FuncPtr= function_name;
* 
* Dereferencing
* data_type x=*FuncPtr;
* 
* We can also use aliases:
* 
* Using Ex = return_type (*) (parameter type, ....);
* 
* So we can use Ex as the parameter and not the name FuncPtr.
* 
* Examples:
* 
#include <iostream>
using namespace std;
 
int multiply(int a, int b) { return a * b; }
 
int main()
{
    int (*func)(int, int);
 
    // func is pointing to the multiplyTwoValues function
 
    func = multiply;
 
    int prod = func(15, 2);
    cout << "The value of the product is: " << prod << endl;
 
    return 0;
}
//////////////////////////////
#include <iostream>
using namespace std;

const int a = 15;
const int b = 2;

// Function for Multiplication
int multiply() { return a * b; }

// Function containing function pointer
// as parameter
void print(int (*funcptr)())
{
    cout << "The value of the product is: " << funcptr()
         << endl;
}

// Driver Function
int main()
{
    print(multiply);
    return 0;
}
* In sort function, we can specialize the comparison operation for different types.
* 
* The disadvantages of function pointers are:
* 1. They can not be optimized at compile time since they use an address of a function, 
* so the compiler doesn't know which function has to call, and therefore it can't be inlined (optimized).
* 2. They point to global functions, which can not have a state. For example, the number of times
* we call the function, we have to store it in a variable which will be shared between the 
* invocations of the function. This means function pointers are callbacks.
* 
* Callbacks can be implemented by function pointers and function objects. We can find more
* information here https://stackoverflow.com/questions/2298242/callback-functions-in-c
* 
* Function objects will be discused in Function Objects solution.
* 
* In C++11 callbacks can be implemented through lambda expressions, and they're better than function pointers 
* and function objects.
*/

using Comparator = bool(*)(int, int);

template<typename T, int size>
void Sort(T(&arr)[size], Comparator comp) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            if (comp(arr[j], arr[j + 1])) {
                // We use std::move to avoid creating copies of elements (for example if we sort user defined objects)
                T temp = std::move(arr[j]);
                arr[j] = std::move(arr[j+1]);
                arr[j+1] = std::move(temp);
            }
        }
    }
}

bool CompIncrement(int x, int y) {
    return x > y;
}

bool CompDecrement(int x, int y) {
    return x < y;
}

int main()
{
    // Declaring and initializing Integer array with custom input entries
    int a[]{ 1, 6, 8, 4, 0 };
    print(a);

    Sort(a, CompIncrement);
    print(a);

    Sort(a, CompDecrement);
    print(a);
    
    return 0;
}