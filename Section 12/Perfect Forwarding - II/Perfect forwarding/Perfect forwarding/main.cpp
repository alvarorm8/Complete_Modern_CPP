#include "Integer.h"
#include <iostream>
#include <string>
class Employee {
	std::string m_Name;
	Integer m_Id;
public:
	//Employee(const std::string &name, const Integer &id) :
	//	m_Name{ name },
	//	m_Id{ id } {
	//	std::cout << "Employee(const std::string &name, const Integer &id)" << std::endl; 
	//}

	/*
	* We have created this constructor so all possible combinations ({lvalue, lvalue}, {lvalue, rvalue}, {rvalue, lvalue}, {rvalue, rvalue})
	* are generated as required by the type of arguments passed to the constructor of Employee.
	* 
	* std::forward is used to preserve the argument type of the variable passed to initialize the class members. For example, if we pass
	* a temporary object to m_Id (with Integer{100} for example), since it has a name, the compiler would call the copy constructor
	* to initialize m_Id, even with the temporary object. With std::forward, the move constructor will be called, as it is expected to do.
	* 
	* IMPORTANT: perfect forwarding only works with template type arguments, because it only works when argument deduction is involved
	*/
	template<typename T1, typename T2>
	Employee(T1 &&name,  T2 &&id) :
		m_Name{ std::forward<T1>(name) },
		m_Id{ std::forward<T2>(id) } {
		std::cout << "Employee(std::string &&name,  Integer &&id)" << std::endl;

	}
};

//We have to use again std::forward since the argument type information is lost when we pass it to the function
template<typename T1, typename T2>
Employee *Create(T1 && a, T2 &&b) {
	return new Employee(std::forward<T1>(a), std::forward<T2>(b));
}
int main() {
	//Employee emp1{ "Umar", Integer{100} };
	/*std::string name = "Umar";
	Employee emp2{ name, 100 };
	Integer val{ 100 };
	Employee emp3{ std::string{"Umar"}, val };*/
	auto emp = Create("Umar", Integer{ 100 });
	return 0;
}