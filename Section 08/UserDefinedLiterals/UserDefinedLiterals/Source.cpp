#include <iostream>
//C++11 allows to define our own literals, appart from the existing ones in C++, like 14u (unsigned integer), 19l(long), L"als" (wide string), etc.
class Distance {
	long double m_Kilometres;
public:
	Distance(long double km) :m_Kilometres{ km } {

	}
	long double GetKm()const {
		return m_Kilometres;
	}
	void SetKm(long double val) {
		m_Kilometres = val;
	}
};
Distance operator"" _mi(long double val) {
	return Distance{ val * 1.6 };
}
Distance operator"" _metres(long double val) {
	return Distance{ val / 1000 };
}
int main() {
	Distance dist{ 32.0_mi };
	Distance d2{ 7123.0_metres };
	std::cout << dist.GetKm() << std::endl;
	std::cout << d2.GetKm() << std::endl;
	return 0;
}