#pragma once
#include <iostream>

namespace Assignment4 {

	class Employee {
		std::string Name;
		int Id;
		int Salary;
	public:
		Employee(): Name{ "" }, Id(0), Salary{0} {}
		Employee(std::string name, int id, int salary): Name{ name }, Id(id), Salary{ salary } {}

		~Employee() { std::cout << "~Employee()" << std::endl; };

		void setName(std::string name) {
			this->Name = name;
		}

		void setId(int id) {
			this->Id = id;
		}

		void setSalary(int salary) {
			this->Salary = salary;
		}

		std::string getName() {
			return this->Name;
		}

		int getId() {
			return this->Id;
		}

		int getSalary() {
			return this->Salary;
		}

		void printClassInfo() const {
			std::cout << "Object of class Employee" << std::endl;
			std::cout << "Name: " << Name << ", Id: " << Id << ", Salary: " << Salary << std::endl;
		}
	};

	class Contact {
		std::string Name;
		int PhoneNumber;
		std::string Address;
		std::string Email;
	public:
		Contact(): Name(""), PhoneNumber(0), Address(""), Email("") {}

		Contact(std::string name, int phoneNumber, std::string address, std::string email):
		Name(name), PhoneNumber(phoneNumber), Address(address), Email(email) {
			std::cout << "name: " << name << std::endl;
		}

		~Contact() { std::cout << "~Contact()" << std::endl; };

		void setName(std::string name) {
			this->Name = name;
		}

		std::string getName() {
			return this->Name;
		}

		int getPhoneNumber() {
			return this->PhoneNumber;
		}

		void setPhoneNumber(int phoneNumber) {
			this->PhoneNumber = phoneNumber;
		}

		void setAddress(std::string address) {
			this->Address = address;
		}

		std::string getAddress() {
			return this->Address;
		}

		void setEmail(std::string email) {
			this->Email = email;
		}

		std::string getEmail() {
			return this->Email;
		}

		void printClassInfo() const {
			std::cout << "Object of class Contact" << std::endl;
			std::cout << "Name: " << Name << ", PhoneNumber: " << PhoneNumber <<
				", Address: " << Address << ", Email: " << Email << std::endl;
		}
	};

	template<typename T, typename...Params>
	T* CreateObject(Params&&... args) {
		return new T{ std::forward<Params>(args)... };
	}

}