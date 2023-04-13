#include <iostream>
#include <vector>
template<typename T>
class PrettyPrinter {
	T* m_pData;
public:
	PrettyPrinter(T* data) :m_pData(data) {

	}
	void Print() {
		std::cout << "{" << *m_pData << "}" << std::endl;
	}

	T* GetData() {
		return m_pData;
	}
};

//Explicit specialization of a member function should appear outside the class
template<>
void PrettyPrinter<std::vector<int>>::Print() {
	std::cout << "{";
	for (const auto& x : *m_pData) {
		std::cout << x;
	}
	std::cout << "}" << std::endl;
}

//Explicit specialization of the class since for char* the main class does not work properly
template<>
class PrettyPrinter<char*> {
	char* m_pData;
public:
	PrettyPrinter(char* data) :m_pData(data) {

	}
	void Print() {
		std::cout << "{" << m_pData << "}" << std::endl;
	}
	char* GetData() {
		return m_pData;
	}
};
//Assignment 5
template<>
void PrettyPrinter<std::vector<std::vector<int>>>::Print() {
	std::cout << "{";
	for (auto it = std::begin(*m_pData); it != std::end(*m_pData); ++it) {
		std::cout << std::endl << "   {";
		for (auto it2 = std::begin(*it); it2 != std::end(*it); ++it2) {
			std::cout << *it2;
			if (it2 != std::end(*it)-1) {
				std::cout << ",";
			}
		}
		std::cout << "}";
		if (it != std::end(*m_pData)-1) {
			std::cout << ",";
		}
		std::cout << std::endl;
	}
	std::cout << "}" << std::endl;
	//Without comma
	/*for (const auto& vec : *m_pData) {
		std::cout << std::endl << "   {";
		for (const auto& vec2 : vec) {
			std::cout << vec2;
		}
		std::cout << "}" << std::endl;
	}
	std::cout << "}" << std::endl;*/
}

//template<>
//class PrettyPrinter<std::vector<std::vector<int>>> {
//	std::vector<std::vector<int>>* m_pData;
//public:
//	PrettyPrinter(std::vector<std::vector<int>>* data) :m_pData(data) {
//
//	}
//	void Print() {
//		std::cout << "{";
//		for (const auto& vec : *m_pData) {
//			std::cout << std::endl << "   {";
//			for (const auto& vec2 : vec) {
//				std::cout << vec2;
//			}
//			std::cout << "}" << std::endl;
//		}
//		std::cout << "}" << std::endl;
//	}
//	std::vector<std::vector<int>>* GetData() {
//		return m_pData;
//	}
//};

//template<>
//class PrettyPrinter<std::vector<int>> {
//	std::vector<int> *m_pData;
//public:
//	PrettyPrinter(std::vector<int> *data) :m_pData(data) {
//
//	}
//	void Print() {
//		std::cout << "{";
//		for (const auto &x : *m_pData) {
//			std::cout << x;
//		}
//		std::cout << "}" << std::endl;
//	}
//	std::vector<int> * GetData() {
//		return m_pData;
//	}
//};
int main() {
	//int data = 5;
	//float f = 8.2f;
	//PrettyPrinter<int> p1(&data);
	//p1.Print();
	//PrettyPrinter<float> p2(&f);
	//p2.Print();

	const char* p = { "Hello world" };
	PrettyPrinter<char*> p3((char*)p);
	p3.Print();
	char* pData = p3.GetData();
	std::vector<int> v{ 1,2,3,4,5 };
	PrettyPrinter<std::vector<int>> pv(&v);
	pv.Print();
	std::vector<int> v2{ 6,7,8,9,10 };
	std::vector<int> v3{ 11,12,13,14,15 };

	std::vector<std::vector<int>> vV{ v,v2,v3 };
	PrettyPrinter<std::vector<std::vector<int>>> pVV(&vV);
	pVV.Print();
	return 0;
}