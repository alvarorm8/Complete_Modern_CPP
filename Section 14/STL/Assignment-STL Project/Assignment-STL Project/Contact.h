#pragma once

#include <iostream>
#include <string>

enum class GroupType : int
{
	Friends = 1,
	Family = 2,
	Coworker = 3,
	Acquaintance = 4,
	Last //don't use, only for iteration
};

std::ostream& operator <<(std::ostream& out, const GroupType& a);

class Contact
{
public:
	std::string FirstName;
	std::string LastName;
	std::string PrimaryPhoneNumber;
	std::string SecondaryPhoneNumber;
	std::string EmailID;
	std::string Address;
	std::string Company;
	GroupType Group;

	Contact() = default;
	Contact(std::string firstName, std::string lastName, std::string primaryPhoneNumber, std::string secondaryPhoneNumber, std::string emailID,
		std::string address, std::string company, GroupType group);
	~Contact() = default;

	void PrintContactInfo() const;

};

