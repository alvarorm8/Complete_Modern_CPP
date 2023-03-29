#pragma once
#include <iostream>
class Integer {
	int* m_pInt;
public:
	//Default constructor
	Integer();
	//Parameterized constructor
	//explicit Integer(int value); // if we define the constructor as explicit, the compiler can not call it implicitly, so the implicit calls in main will fail
	Integer(int value);
	//Copy constructor
	Integer(const Integer& obj);
	//Move constructor
	Integer(Integer&& obj);
	int GetValue()const;
	void SetValue(int value);
	~Integer();
	Integer& operator ++();
	Integer operator ++(int);
	bool operator ==(const Integer& a)const;

	//Copy assignment
	Integer& operator =(const Integer& a);
	//Move assignment
	Integer& operator =(Integer&& a);
	Integer operator +(const Integer& a)const;

	void operator ()();

	operator int(); // Type conversion operator, to convert user defined class to primitive, for example: int x = Integer object
};
Integer operator +(int x, const Integer& y);
std::ostream& operator <<(std::ostream& out, const Integer& a);
std::istream& operator >> (std::istream& input, Integer& a);
