#pragma once
#include "Account.h"
class Checking :
	public Account {
	float m_MinimumBalance;
public:
	/*
	* using Account::Account; 
	* C++11 functionality to inherit all the constructors from the base class, so we don't need to implement the constructor
	* of the child class. So for this class, if we don't have m_MinimumBalance, we can inherit those constructors from base
	* class, and we can initialize an object of this class like this in main:
	* 
	* Checking check{"bob", 1000};
	* 
	* And it will call the base class constructor correctly.
	* 
	* So, if our child class doesn't have any attributes, we can do that.
	*/
	using Account::Account; 
	Checking(const std::string &name, float balance, float minbalance);
	~Checking();
	void Withdraw(float amount)override;
	float GetMinimumBalance()const;
};

