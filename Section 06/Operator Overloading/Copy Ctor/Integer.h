#pragma once
#include <iostream>
class Integer {
	int *m_pInt;
public:
	//Default constructor
	Integer();
	//Parameterized constructor
	Integer(int value);
	//Copy constructor
	Integer(const Integer &obj);
	//Move constructor
	Integer(Integer &&obj);

	int GetValue()const;
	void SetValue(int value);
	~Integer();

	//Pre increment operator, returns a reference (does not create a copy)
	//is more efficient due to that reason than the post increment
	Integer & operator ++();

	//Post increment operator, returns a value (creates a copy)
	//is less efficient than pre increment due to that reason
	Integer operator ++(int);

	//Comparison operator
	bool operator ==(const Integer &a)const;

	//Copy assignment
	Integer & operator =(const Integer &a);

	//Move assignment
	Integer & operator =(Integer &&a);

	//Sum operator
	Integer operator +(const Integer & a)const;

	//Function operator. Accepts any number of arguments, in this case, 0. When an object obj of the class is called like obj(), that calls this operator
	void operator ()();

	//Friend keyword (used as last resource, since it is very dangerous to allow access all members.
	
	//We declare this function friend of our class to access all members, not necessary, just as example
	friend std::istream& operator >> (std::istream& input, Integer& a);

	//We can declare a class as friend to access all the members of this class
	friend class Printer;
};

//GENERAL NOTE: IF THE FIRST ARGUMENT OF THE OPERATOR IS NOT AN OBJECT OF THE CLASS (example: 5 + Integer object)
//THE OPERATOR HAS TO BE DEFINED AS A GLOBAL FUNCTION, LIKE THE ONES BELOW

//Define global function to do N + Integer. Integer + N is done with the operator + inside the class
Integer operator +(int x, const Integer &y);

//We need to define operators << and >> as global functions because we can't overload the functions in iostream
//We return a reference because it is not a local variable
std::ostream & operator <<(std::ostream & out, const Integer &a);
std::istream & operator >> (std::istream &input, Integer &a);

class Printer {

};