#pragma once
#include <string>
class Account {
	std::string m_Name;
	int m_AccNo;
	static int s_ANGenerator;
protected:
	float m_Balance;
public:
	/*
	* virtual keyword allows that when we call a method through a pointer to the base class the function called is the one of the object that the pointer
	* is pointing at, not the one of the type of pointer. If the pointer points at an object of the child class, the child method will be
	* called, and not the base class method.
	* 
	* In that way, the destructor of a class that will be inherited or has any member like a pointer, a resource, etc., must
	* be virtual also. This is because in the destruction of the objects through a pointer to the base class, if the destructor of the base class
	* is not virtual, only the destructor of the base class will be called, and not the destructors of the child classes, and maybe there will be
	* memory leaks.
	* 
	* If a function defined with virtual is not overrided in the child classes, it does not matter, since it will call the implementation of the base class.
	* This of course is possible if the function is not pure virtual (functions which in the base class don't have any implementation, only definition).
	* Pure virtual functions need to be overrided in all child classes, since it wouldn't have an implementation to call.
	*/
	Account(const std::string &name, float balance);
	virtual ~Account();
	const std::string GetName()const;
	float GetBalance()const;
	int GetAccountNo()const;

	virtual void AccumulateInterest();
	virtual void Withdraw(float amount);
	void Deposit(float amount);
	virtual float GetInterestRate()const;
};

