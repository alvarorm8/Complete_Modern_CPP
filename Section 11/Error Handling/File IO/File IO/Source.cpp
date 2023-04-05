#include <iostream>
#include <fstream>
#include <string>
void Write() {
	std::ofstream out{"data.txt"};
	/*
	* You can also do this way
	* std::ofstream out;
	* out.open("data.txt");
	*/
	out << "Hello world" << std::endl;
	out << 10 << std::endl; 
	out.close(); //if you don't close the file, it will be closed when the object is destroyed
}
void Read() {
	std::ifstream input{ "data.txt" };
	/*
	* You can also do this way
	* std::ifstream input;
	* input.open("data.txt");
	*/
	//if (!input.is_open()) {
	//	std::cout << "Could not open the file" << std::endl;
	//	return;
	//}
	// Same behaviour but with fail bit instead of is_open function
	if (input.fail()) {
		std::cout << "Could not open the file" << std::endl;
		return;
	}
	std::string message;
	std::getline(input, message);
	int value{};
	input >> value; // reads until the first space is found
	input >> value;
	if (input.eof()) { //when eof is reached, failbit is set to true and goodbit is set to false
		std::cout << "End of file encountered" << std::endl;
	}
	if (input.good()) {
		std::cout << "I/O operations are successful" << std::endl;
	}
	else { //fail()
		std::cout << "Some I/O operations failed" << std::endl;
	}
	input.setstate(std::ios::failbit); //set state, it sets the bit with the current value with an or operation
	input.clear(); //clear state flags, puts good bit at true and all the others at false
	input.close();
	std::cout << message << ":" << value << std::endl; 
}
int main() {
	Write();
	Read();
	return 0;
}