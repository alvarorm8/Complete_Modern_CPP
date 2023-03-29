#include <iostream>
class Employee ;
class Project {
public:
	std::shared_ptr<Employee> m_emp ;
	Project() {
		std::cout << "Project()" << std::endl; 
	}
	~Project() {
		std::cout << "~Project()" << std::endl; 
	}
};
class Employee {
public:
	//std::shared_ptr<Project> m_prj ;
	std::weak_ptr<Project> m_prj ;
	Employee() {
		std::cout << "Employee()" << std::endl; 
	}

	~Employee() {
		std::cout << "~Employee()" << std::endl; 
	}
};

int main() {
	std::shared_ptr<Employee> emp{new Employee{}} ;
	std::shared_ptr<Project> prj{new Project{}} ;
	emp->m_prj = prj ;
	prj->m_emp = emp ;

	/*
	* Shared pointers to Employee: emp and m_emp, total count: 2
	* Shared pointers to Project: prj, total count: 1
	* 
	* If emp is destroyed first, the count block of the shared pointers to Employee is decremented by one, and in this case, it will be one, since 
	* the only shared pointer to Employee remaining is m_emp inside the Project object. Later, when prj is destroyed, the references to Project are
	* decremented to 0 and therefore, the Project object will be destroyed from memory. 
	* If the Project object is destroyed, the weak pointer in Employee object is destroyed since there are no references to Project, and the pointer 
	* to Employee m_emp inside the Project object will be destroyed, decrementing the references to Employee to 0, so the Employee object will be deleted
	* from memory. Then no memory leaks occur.
	* 
	* Shared pointers to Employee: emp and m_emp, total count: 2
	* Shared pointers to Project: prj and m_prj, total count: 2
	* 
	* If both pointers inside classes are shared pointers, when emp is destroyed the count block of becomes 1, remaining only m_emp as reference to Employee. 
	* When prj is destroyed, the count block is decremented by one and becomes 1, remaining only m_prj as reference to Project.
	* Then, the pointers to Employee and Project are not destroyed, so memory leaks occur.
	*/
}