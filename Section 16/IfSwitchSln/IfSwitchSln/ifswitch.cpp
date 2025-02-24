#include <iostream>
#include <fstream>
#include <filesystem>
void Alloc() {
	int* p = (int *)malloc(sizeof(int));
	if (p != nullptr) {
		*p = 50;
		free(p);
	}
	
	//Syntax: if (initialization; condition) {
	//we can define the variable p inside the if, like the iterator in a for loop, This is useful for variables we don't want to use outside the loop
	if (int* p = (int*)malloc(sizeof(int)); p != nullptr) { 
		*p = 50;
		free(p);
	}
	else {
		//Here p will be nullptr
	}
}
void Write(const std::string& data) {
	
	//We can combine conditions as usual
	if (std::ofstream out{ "file.txt" }; out && !data.empty()) {
		std::cout << "Writing data into the file\n";
		out << data;
	}
	else {
		std::cout << "Not data to write\n" ;
		out << "####";
	}

	///More statements

}

class FileInfo {
public:
	enum Type{Executable, Text};
	Type GetFileType()const {
		return {} ;
	}
	size_t GetFileSize()const {
		return 0 ;
	}
};

FileInfo GetInfo(const std::string &file) {
	return {} ;
}

void Operate(const std::string &file) {
	
	//We can do the same with switch statements apart from if
	switch (auto info = GetInfo(file) ;info.GetFileType()) {
	case FileInfo::Executable:
		break ;
	case FileInfo::Text:
		break ;
	default:
		break ;
	}
	//More statements
}

int main(){
	Write("") ;
}