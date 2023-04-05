#include <iostream>
#include <fstream>
#include <string>

void Write() {
	std::ofstream out{ "test.txt" };
	if (!out) {
		std::cout << "Could not open file for writing" << std::endl;
		return;
	}
	std::cout << "Current position is: " << out.tellp() << std::endl; //get current position of writing pointer, default 0, error: -1
	std::string message{ "C++ was invented by Bjarne" };
	for (char ch : message) {
		out.put(ch);
	}
	out.seekp(5); //set position to write
	out.put('#');
}

void Read() {
	std::ifstream input{ "test.txt" };
	if (!input) {
		std::cout << "Could not open file for reading" << std::endl;
		return;
	}
	input.seekg(5); // set position to read
	//input.seekg(5, std::ios::beg); //offset, initial position at beginning
	//input.seekg(5, std::ios::cur); //offset, initial position at current position
	//input.seekg(-5, std::ios::beg); //offset, initial position at end of file
	std::cout << "Current position is: " << input.tellg() << std::endl; //get current position of reading pointer, default 0, error: -1
	char ch{};
	while (input.get(ch)) {
		std::cout << ch;
	}
}

void UsingFstream() {
	std::fstream stream{ "file.txt" };
	if (!stream) { //fstream does not create the file if it does not exist
		std::cout << "File does not exist. Creating one..." << std::endl;
		std::ofstream out{ "file.txt" };
		out.close();
		stream.open("file.txt");
	}
	stream << "Hello world" << std::endl;
	//After writing to file get pointer and put pointer are at the end of it.
	stream.seekg(0);
	std::string line;
	std::getline(stream, line);
	std::cout << line << std::endl;
}

int main() {
	Write();
	Read();
	return 0;
}