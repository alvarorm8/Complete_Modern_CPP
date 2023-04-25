#include <iostream>
#ifdef __has_include //used to chech if a header is available for inclusion or not. Used with #if and #elif only
#	if __has_include(<windows.h>)
#		include <filesystem>
		namespace fs = std::filesystem ;
#	else
#		include <experimental/filesystem>
#		namespace fs = std::experimental::filesystem ;
#	endif
#endif

int main() {
	fs::path p{"C:"} ;
	
	std::cout << __cpp_inline_variables << std::endl; //expands to date when this funcionality was added, macros like this where added in C++20
	std::cout << __cpp_capture_star_this << std::endl; 
}