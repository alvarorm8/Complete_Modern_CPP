#pragma once
#include <iostream>
class Integer {
	int *m_pInt;
public:
	/*

	* Rule of 5
	In general, if a class has resources like pointers, access to databases, sockets, etc., the following members must be defined:
	1. Destructor
	2. Copy Constructor
	3. Copy assignment operator
	4. Move constructor
	5. Move assignment operator

	* Rule of 0

	In general, if a class does not have any resources like pointers, etc., we should not implement any of the previous members.
	If a member is defined, the compiler does not synthesize the other. If we don't provide any, the compiler will synthesize the
	5 members.

	*/

	//Default constructor
	Integer();

	//Parameterized constructor
	Integer(int value);

	//Copy constructor
	Integer(const Integer &obj);

	//Move constructor
	Integer(Integer &&obj);

	//Copy assignment
	Integer & operator=(const Integer &obj) ;

	//Move assignment
	Integer & operator=(Integer && obj) ;

	int GetValue()const;
	void SetValue(int value);
	~Integer();

};
