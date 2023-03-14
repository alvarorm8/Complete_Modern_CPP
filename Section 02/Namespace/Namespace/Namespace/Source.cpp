#include <iostream>

namespace Avg {
	float Calculate(float x, float y) {
		return (x + y) / 2;
	}
}

namespace Basic {
	float Calculate(float x, float y) {
		return x + y;
	}
}
namespace Sort {
	void Quicksort() {

	}
	void Insertionsort() {

	}
	void Mergesort() {

	}
	namespace Comparision {
		void Less() {

		}
		void Greater() {

		}
	}
}
namespace {
	// si el namespace no tiene nombre, los miembros solo son visibles en el scope en el que se define,
	// en este caso, en Source.cpp. Si se define dentro de otro namespace, solo seria visible dentro 
	// de ese namespace, etc.
	void InternalFunction() {

	}
}
int main() {
	//Avoid opening a namespace at a global scope
	
	InternalFunction();
	using namespace Sort::Comparision;
	Less();
	Sort::Comparision::Less(); // nombre completo
	return 0;
}