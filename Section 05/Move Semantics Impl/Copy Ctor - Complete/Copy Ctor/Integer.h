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
	/*
	Move semantics is used to be faster than copy constructor. This is because it doesn't create new instances of pointers, resources, etc.,
	like a copy constructor should do. Instead, it moves the resources from one object to another, and it releases the resources from the first
	object (if they're not released, it would be the same as shallow copy, which is wrong). This is used for temporary objects.
	*/
	Integer(Integer &&obj);
	int GetValue()const;
	void SetValue(int value);
	~Integer();

};
