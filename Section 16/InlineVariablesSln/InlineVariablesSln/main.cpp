/*
* We want to define a global variable and use it in several .cpp files. If we declare it in vars.h and use it in a.cpp, b.cpp and main.cpp 
* including the vars.h in .cpp files, the compiler will throw an error because the variable is being defined at each .cpp file.
* 
* To solve it, we can declare the variable in the header file as extern. 
* 
* In C++17, another way was added, through the inline keyword. Inline has the same effect as in functions and it assures that even if there are
* several definitions of the variable in .cpp files, the compiler will only get one.
* 
* We can use inline also in static members of classes. Before, if we define a static variable in a class, we have to initialize it in a .cpp file, 
* for example in vars.h in class Test, the initialization in main.cpp would be Test::m_Data = 20;. Now, we can use inline to initialize the variable
* in the header file.
* 
* This way, you can initialize all variables in header file, since normal variables can be initialized in the .h file.
* 
* constexpr static member variables are implicitly inline variables.as
*/
#include <iostream>
#include "vars.h"

int main() {
	
}