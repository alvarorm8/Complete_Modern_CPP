#include "Contact.h"

Contact::Contact(std::string firstName, std::string lastName, std::string primaryPhoneNumber, std::string secondaryPhoneNumber, std::string emailID, std::string address, std::string company, GroupType group)
	: FirstName{ firstName }, LastName{ lastName }, PrimaryPhoneNumber{ primaryPhoneNumber },
	SecondaryPhoneNumber{ secondaryPhoneNumber }, EmailID{ emailID }, Address{ address }, Company{ company }, Group{ group } {
	std::cout << "Contact parametrized constructor" << std::endl;
}

void Contact::PrintContactInfo() const {
	std::cout << std::endl;
	std::cout << "FirstName: " << FirstName << std::endl;
	std::cout << "LastName: " << LastName << std::endl;
	std::cout << "PrimaryPhoneNumber: " << PrimaryPhoneNumber << std::endl;
	std::cout << "SecondaryPhoneNumber: " << SecondaryPhoneNumber << std::endl;
	std::cout << "EmailID: " << EmailID << std::endl;
	std::cout << "Address: " << Address << std::endl;
	std::cout << "Company: " << Company << std::endl;
	std::cout << "Group: " << Group << std::endl;
	std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& out, const GroupType& a)
{
	if (a == GroupType::Acquaintance) {
		out << "Acquaintance";
	}
	else if (a == GroupType::Coworker) {
		out << "Coworker";
	}
	else if (a == GroupType::Family) {
		out << "Family";
	}
	else if (a == GroupType::Friends) {
		out << "Friends";
	}
	return out;
}
