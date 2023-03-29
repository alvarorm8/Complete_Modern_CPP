
#include <iostream>
#include <string>

/*
* shared_ptr is used when we want to share the value of pointer with other parts of the code.
* In this case, for example, we share the Project prj pointer between different Employee objects.
* 
* If we use unique_ptr here, the Project pointer would be moved to the Project pointer inside the first 
* Employee object Project pointer (m_pProject), so in the other Employee objects, when we do the SetProject
* we are passing a nullptr. Also, when calling prj->ShowProjectDetails(), the pointer would be nullptr, and 
* the code would crash.
* 
* With shared_ptr, the copy is supported so move is not recommended, since the source pointer would be nullptr after copy.
* In this case, copy is done.
* 
* Inside shared_ptr the count of copies of the shared_ptr is maintained in all copies, and we can check it with use_count().
* In this case, there would be 4 copies (the object prj and inside each one of the Employee objects).
* 
* If a modification is done through any of the object which holds a reference to the shared pointer, the change is made in
* all objects.
*/
class Project {
	std::string m_Name ;
public:
	void SetName(const std::string &name) {
		m_Name = name ;
	}
	void ShowProjectDetails()const {
		std::cout << "[Project Name]" << m_Name << '\n' ;
	}
};

class Employee {
	std::shared_ptr<Project> m_pProject{} ;
public:
	void SetProject(const std::shared_ptr<Project> &prj) {
		m_pProject = prj ; //copy assignment is done
	}
	const std::shared_ptr<Project>& GetProject()const {
		return m_pProject ;
	}
};
void ShowInfo(const std::shared_ptr<Employee> & emp) {
	std::cout << "Employee project details:" ;
	emp->GetProject()->ShowProjectDetails() ;
}
int main() {
	std::shared_ptr<Project> prj { new Project{}} ;
	prj->SetName("Video Decoder") ;
	std::shared_ptr<Employee> e1 {new Employee{}} ;
	e1->SetProject(prj) ;
	std::shared_ptr<Employee> e2 { new Employee{} };
	e2->SetProject(prj) ;
	std::shared_ptr<Employee> e3 { new Employee{}} ;
	e3->SetProject(prj) ;

	e3.reset(new Employee{}) ;//the pointer is reset, so all resources are freed, in this case, references to prj are decrement by 1.
	if(e3) {
		//Valid
	}else {
		//Not valid
	}
	
	std::cout << "Reference count in prj:" << prj.use_count() << '\n' ;
	std::cout << "Reference count in e1:" << e1.use_count() << '\n' ;

	e1->GetProject()->SetName("Video Decoder Version 2.0");
	ShowInfo(e1) ;
	ShowInfo(e2) ;//info is changed also in e2
	prj->ShowProjectDetails() ;

}
