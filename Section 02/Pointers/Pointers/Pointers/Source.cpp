#include <iostream>

int Add(int* a, int* b); //Add two numbers and return the sum
void AddVal(int* a, int* b, int* result); //Add two numbers and return the sum through the third pointer argument
void Swap(int* a, int* b);  //Swap the value of two integers
void Factorial(int* a, int* result); //Generate the factorial of a number and return that through the second pointer argument


int main() {
	using namespace std;
	int x = 5;
	cout << x << "\n";
	//Always try to initialize pointers to nullptr
	int *ptr = nullptr;
	//cout << *ptr << "\n"; //error at runtime trying to print null pointer
	//*ptr = 5; // error at runtime, trying to write to nullptr
	ptr = &x;

	//void ptr can point to any kind of variable
	void *ptr2 = &x;

	int result = 0;
	int *ptr3 = &result;
	Factorial(ptr, ptr3);
	cout << *ptr3 << endl;

	// Con uniform initialization
	int * p = new int{};
	int* p2 = new int{ 10 };
	char * p3 = new char[10]{};
	char* p4 = new char[] {"Hello"};
	return 0; 
}

int Add(int* a, int* b) {
	return (*a + *b);
}
void AddVal(int* a, int* b, int* result) {
	*result = *a + *b;
}
void Swap(int* a, int* b) {
	int c = *a;
	*a = *b;
	*b = c;
}
void Factorial(int* a, int* result) {
	*result = 1;
	for (int i{ 1 }; i <= *a; i++) {
		*result *= i;
	}
}
