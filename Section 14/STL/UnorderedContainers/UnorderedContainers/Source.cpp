#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
void UnSet() {
	/*
	* Associative container implemented as hash tables
	* Elements are stored based on the hash, but in unspecified order, the hash acts as a key
	* In a basic implementation, a hash table is an array where each element is a bucket or slot.
	* The value is passed through a function which computes the hash and stores it in the hash table
	* as a key or index.
	* 
	* Fast search, insertion/deletion, but may degrade over time. Faster than its equivalent ordered container.
	* std::unordered_set stores values that act as keys for hashing
	* std::unordered_map stores pairs (first is used to compute hash)
	* Iterators are constant, you can't modify elements through them
	* 
	* Only unordered_multiset allows multiple elements with the same value
	*/
	std::unordered_multiset<std::string> coll; //the second operator is the hash function
	coll.insert("Hulk");
	coll.insert("Batman");
	coll.insert("Green Lantern");
	coll.insert("The Flash");
	coll.insert("Wonder Woman");
	coll.insert("Iron man");
	coll.insert("Iron man");
	coll.insert("Iron man");
	coll.insert("Wolverine");
	coll.insert("Dr. Strange");
	coll.insert("Hawkman");

	
	for (const auto x : coll) { 
		//bucket and copntent of it. A bucket can contain several values. When this value grows, the performance is reduced when searching, etc.
		std::cout << "Bucket #:" << coll.bucket(x) << " contains :" << x << std::endl;
	}
	std::cout << "Bucket count:" << coll.bucket_count() << std::endl; // capacity
	std::cout << "Number of elements:" << coll.size() << std::endl;
	std::cout << "Load factor:" << coll.load_factor() << std::endl ;
	//Load factor is the % filled of the capacity of the hash table. When it is overloaded, it is automatically resized by reallocation and rehashing the elements.
}
void UnMap() {
	/*
	* unordered_map, unordered_multimap are the same as unordered_set and unordered_multiset but with pairs, where the first element is the key and the second the value
	*/
	std::unordered_multimap<std::string, std::string> coll;
	//Only unordered_map support [] operator, not multimap
	/*coll["Batman"] = "Brue Wayne";
	coll["Superman"] = "Clark Kent";
	coll["Hulk"] = "Bruce Banner";*/
	coll.insert(std::make_pair("Batman", "Bruce Wayne"));
	coll.insert(std::make_pair("Batman", "Matches Malone"));
	coll.insert(std::make_pair("Superman", "Clark Kent"));
	coll.insert(std::make_pair("Hulk", "Bruce Banner"));

	for (const auto &x : coll) {
		std::cout << "Bucket #:" << coll.bucket(x.first) << " ->" << x.first << ":" << x.second << std::endl; 
	}
}
class Employee {
	/*
	* For ordered containers, when you want to store used defined objects in stl containers, you have to overload comparison operators <, >, != and ==
	* to apply sort, for example. If they're not overloaded it will be a compiler error. Not always needed, you can specify with a lambda the operator (seen in Algorithms solution)
	* 
	* For unordered containers, you have to provide a function object for hashing (EmployeeHash) and another for equality (EmpEquality).
	*/
	std::string m_Name;
	int m_Id;
public:
	Employee(const std::string &n, int id) :m_Name(n), m_Id(id) {

	}
	const std::string & GetName()const {
		return m_Name;
	}
	int GetId()const {
		return m_Id;
	}
};

//Custom hash function
struct EmployeeHash {
	size_t operator()(const Employee & emp)const {
		auto s1 = std::hash<std::string>{}(emp.GetName());
		auto s2 = std::hash<int>{}(emp.GetId());
		return s1 ^ s2; //xor. Ideally you use the hash combine function from the boost library
	}
};
//Custom function object for equality. You have to compare all the attributes used to generate the hash value (in EmployeeHash)
struct EmpEquality {
	bool operator()(const Employee &e1, const Employee e2)const {
		return e1.GetId() == e2.GetId() && e1.GetName() == e2.GetName();
	}
};
void Hashes() {
	std::hash<std::string> h;
	//Hash is computed by the function object
	std::cout << "Hash:" << h("Hello") << std::endl;


	std::unordered_set<Employee, EmployeeHash, EmpEquality> coll;
	coll.insert(Employee("Umar", 123));
	coll.insert(Employee("Bob", 678));
	coll.insert(Employee("Joey", 612));

	for (const auto &x : coll) {
		std::cout << x.GetId() << ":" << x.GetName() << std::endl;
	}
}
int main() {
	Hashes();
	return 0;
}