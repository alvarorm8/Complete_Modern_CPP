#include <iostream>

int main() {
	using namespace std;
	int arr[] = { 1,2,3,4,5 };
	for (int i = 0; i < 5; i++) {
		cout << arr[i] << " ";
	}
	for (const auto & x : arr) { 
		// si no ponemos & crea una copia del elemento en x en cada iteracion, para evitarlo, se usa & y, para evitar que se modifique el valor
		// del array, se puede poner const
		cout << x << " ";
	}
	for (auto x : { 1,2,3,4 }) {
		cout << x << endl;
	}
	for (const auto & x : arr) {
		cout << x << endl;
	}
	return 0;
}