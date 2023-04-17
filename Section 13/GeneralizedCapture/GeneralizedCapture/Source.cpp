/*
* Generalized Capture is a feature introduced in C++14.
* 
* This allows the creation of new variables inside the capture clause, whose type is deduced from the
* type produced by the expression which initialize the variables.
* 
* [var = expression](args) //creation of a variable
* [&var = expression](args) //creation of a reference
*/
#include <iostream>
#include <fstream>
int main() {
	int x{ 5 };
	auto f = [y = x](int arg) {
		return y + arg;
	};
	std::cout << f(5) << std::endl;

	/*std::ofstream out{ "file.txt" };
	auto write = [&out](int x) {
		out << x;
	};*/

	/*
	* The previous expression works, but if we want to use the object out only in the lambda expression
	* we can use generalized capture to do it:
	*/
	std::ofstream out{ "file.txt" };
	auto write = [out = std::move(out)](int x)mutable { //we have to use mutable to modify the out variable
		out << x;
	};

	// This could be usefull too with an unique ptr we want to capture in the lambda.

	write(90);
	return 0;
}