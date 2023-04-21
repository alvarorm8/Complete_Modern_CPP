#include "Contact.h"
#include <set>
#include <vector>
#include <algorithm>

const int MAX_ATTEMPS{ 5 };

struct ContactComparator {
	bool operator()(const Contact &c1, const Contact& c2)const {
		return c1.FirstName < c2.FirstName;
	}
};
////////////////// 1 //////////////////
void SortContacts(std::vector<Contact> &contacts) {
	std::cout << "Please, introduce option for sort (0 = First name, 1 = Last name): ";
	int option{-1};
	int attemps{ 0 };
	while (option != 0 && option != 1) {
		std::cin.clear();
		std::cin >> option;
		if (attemps >= MAX_ATTEMPS) {
			std::cout << "Max number of attemps (" << MAX_ATTEMPS << ") reached, exiting the sort function" << std::endl;
			return;
		}
		std::cout << std::endl << "Not valid choice, please insert a valid option (0 = First name, 1 = Last name): ";
		attemps++;
	}
	if (option == 0) {
		std::sort(contacts.begin(), contacts.end(), [](const auto& e1, const auto& e2) {
			return e1.FirstName < e2.FirstName;
			});
	}
	else {
		std::sort(contacts.begin(), contacts.end(), [](const auto& e1, const auto& e2) {
			return e1.LastName < e2.LastName;
			});
	}
	for (const Contact &cont : contacts)
		cont.PrintContactInfo();
}
////////////////// 2 //////////////////
void DisplayFirstNameAndNumber(std::vector<Contact>& contacts) {
	for (const Contact& cont : contacts) {
		std::cout << "FirstName: " << cont.FirstName << std::endl;
		std::cout << "PrimaryPhoneNumber: " << cont.PrimaryPhoneNumber << std::endl;
	}
}
////////////////// 3 //////////////////
void DisplayContactsFromCompanies(std::vector<Contact>& contacts, std::string company) {
	//As for_each returns a copy of the function object passed, in the case of a lambda, returns the variables passed in []
	//In this case, companyContacts is formed by company
	auto companyContacts = std::for_each(contacts.begin(), contacts.end(), [company](const Contact& emp) {
		if (emp.Company == company)
			emp.PrintContactInfo();
	});
}

//Same function but saving in a vector the result
void DisplayContactsFromCompanies2(std::vector<Contact>& contacts, std::string company) {
	std::vector<Contact> contacsFromCompany{};
	//As for_each returns a copy of the function object passed, in the case of a lambda, returns the variables passed in []
	//In this case, companyContacts is formed by company and contacsFromCompany
	auto companyContacts = std::for_each(contacts.begin(), contacts.end(), [company, &contacsFromCompany](const Contact& emp) {
		if (emp.Company == company)
			contacsFromCompany.emplace_back(emp);
	});
	for (Contact cont : contacsFromCompany) {
		cont.PrintContactInfo();
	}
}
////////////////// 4 //////////////////
void DisplayContactsFromGroup(std::vector<Contact>& contacts, GroupType group) {
	//As for_each returns a copy of the function object passed, in the case of a lambda, returns the variables passed in []
	//In this case, companyContacts is formed by company
	auto companyContacts = std::for_each(contacts.begin(), contacts.end(), [group](const Contact& emp) {
		if (emp.Group == group)
			emp.PrintContactInfo();
		});
}
////////////////// 5 //////////////////
Contact* SearchContactByName(std::vector<Contact>& contacts, int option, std::string name) {
	auto itr = std::find_if(contacts.begin(), contacts.end(), [option, name](const auto& e) {
		if (option == 1) {
			return e.FirstName == name;
		}
		else {
			return e.LastName == name;
		}
	});
	if (itr != contacts.end()) {
		return &(*itr);
	} else {
		if (option == 1)
			std::cout << "Contact with first name \"" << name << "\" not found." << std::endl;
		else
			std::cout << "Contact with last name \"" << name << "\" not found." << std::endl;
		return nullptr;
	}
}
////////////////// 6 //////////////////
void DisplayNumberOfContactsByCompany(std::vector<Contact>& contacts) {
	std::set<std::string> companies{};
	for (Contact cont : contacts) {
		if (!companies.contains(cont.Company)) {
			companies.emplace(cont.Company);
			int count{ 0 };
			std::count_if(contacts.begin(), contacts.end(), [cont, &count](const Contact& emp) {
				if (emp.Company == cont.Company)
					++count;
				return count;
			});
			std::cout << "For the company " << cont.Company << " there are " << count << " contacts." << std::endl;
		}
	}
}

void DisplayNumberOfContactsByGroup(std::vector<Contact>& contacts) {
	std::set<std::string> companies{};
	for (GroupType groupType = GroupType::Friends; groupType < GroupType::Last; groupType = static_cast<GroupType>((size_t)groupType+1))
	{
		std::string groupName{};
		if (groupType == GroupType::Friends)
			groupName = "Friends";
		else if (groupType == GroupType::Family)
			groupName = "Family";
		else if (groupType == GroupType::Coworker)
			groupName = "Coworker";
		else if (groupType == GroupType::Acquaintance)
			groupName = "Acquaintance";

		int count{ 0 };
		std::count_if(contacts.begin(), contacts.end(), [groupType, &count](const Contact& emp) {
			if (emp.Group == groupType)
				++count;
			return count;
		});
		std::cout << "For the group " << groupName << " there are " << count << " contacts." << std::endl;
	}
}
int main() {
	std::vector<Contact> contacts{
		Contact{ "Alvaro", "Ramirez", "+34600100200", "+34600100201", "alvaro.r@gmail.com", "C/Falsa 123", "Indra S.A.", GroupType::Family },
		Contact{ "Laura", "Ramirez", "+346100200300", "+346100200301", "laura.r@gmail.com", "C/Falsa 111", "Thales S.A.", GroupType::Family },
		Contact{ "Jose Manuel", "Lopez", "+346200300400", "+346200300401", "jose_manuel.l@gmail.com", "C/Falsa 134", "Airbus S.A.", GroupType::Acquaintance},
		Contact{ "Cristian", "Ramos", "+346200300407", "+346200300405", "jose_manuel.l@gmail.com", "C/Falsa 188", "CocaCola S.A.", GroupType::Acquaintance},
		Contact{ "Marta", "Campos", "+34630400500", "+34630400501", "marta.c@gmail.com", "C/Falsa 187", "Indra S.A.", GroupType::Coworker },
	};

	contacts.emplace_back("Pepe", "Mendez", "+34630400504", "+34630400508", "pepe.m@gmail.com", "C/Falsa 230", "Indra S.A.", GroupType::Coworker);
	contacts.emplace_back("Paco", "Flores", "+34630400575", "+34630400565", "paco.f@gmail.com", "C/Falsa 233", "Gillete S.A", GroupType::Friends);
	contacts.emplace_back("Julia", "Otero", "+34630400557", "+34630400534", "julia.o@gmail.com", "C/Falsa 235", "CocaCola S.A.", GroupType::Friends);

	int option{ 7 };

	if (option == 1)
		SortContacts(contacts);
	else if (option == 2)
		DisplayFirstNameAndNumber(contacts);
	else if (option == 3)
		DisplayContactsFromCompanies(contacts, "Indra S.A.");
	else if (option == 4)
		DisplayContactsFromGroup(contacts, GroupType::Friends);
	else if (option == 5) {
		auto contact = SearchContactByName(contacts, 1, "Alvaro");
		if (contact != nullptr) {
			contact->PrintContactInfo();
		}
	}
	else if (option == 6) {
		DisplayNumberOfContactsByCompany(contacts);
	}
	else if (option == 7) {
		DisplayNumberOfContactsByGroup(contacts);
	}

	return 0;
}