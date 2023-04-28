#include <iostream>
#include <filesystem>
/*
* C++17 introduces filesystem library, which provides facilities to do:
* - Manipulation of filesystem path
* - Create, move, rename, delete directories
* - List contents of a given directory
* - Get information about path, file permissions, etc.
* 
* But, for read & write files, we have to use stream library.
* 
* It is in <filesystem> header under std::filesystem namespace
* The main classes are:
* - path: allows manipulation of paths that represent existing files or directories
* - directory_entry: represents a path with additional information such as file size, file times, etc.
* - directory_iterator: an iterator that iterates over the contents of a directory
* ...
* - functions for working with directories
* ...
* 
* Many functions will throw std::filesystem_error exception, others can return an error code.
* Usually, there are two overloaded functions of the same, one returns an error code and the other
* throws an exception.
*/
namespace fs = std::filesystem ;
void UsingPath() {
	fs::path selectedPath{R"(E:\Data\Material\C++\Assignments.docx)"} ;
	std::cout << selectedPath << std::endl;//prints path with \\ since it has to escape the \ character
	std::cout << selectedPath.string() << std::endl; //prints generic path

	selectedPath.remove_filename() ; //removes filename, remaining E:\Data\Material\C++
	//selectedPath /= "newfile" ; // \ separator is added automatically \newfile
	//selectedPath.append("newfile"); //another way of adding info
	
	if (selectedPath.has_root_name()) {
		std::cout << "root name\t = " << selectedPath.root_name().string() << std::endl;
	}
	if (selectedPath.has_root_path()) {
		std::cout << "root path\t = " << selectedPath.root_path().string() << std::endl;
	}
	if (selectedPath.has_root_directory()) {
		std::cout << "root directory\t = " << selectedPath.root_directory().string() << std::endl;
	}
	if (selectedPath.has_parent_path()) {
		std::cout << "parent path\t = " << selectedPath.parent_path().string() << std::endl;
	}
	if (selectedPath.has_relative_path()) {
		std::cout << "relative path\t = " << selectedPath.relative_path().string() << std::endl;
	}
	if (selectedPath.has_filename()) {
		std::cout << "filename\t = " << selectedPath.filename().string() << std::endl;
	}
	if (selectedPath.has_stem()) {
		std::cout << "stem part \t = " << selectedPath.stem().string() << std::endl;
	}
	if (selectedPath.has_extension()) {
		std::cout << "extension\t = " << selectedPath.extension().string() << std::endl;
	}
}

void TraversingDirectory(std::string_view file) {
	fs::path currentPath{file} ;
	std::vector<fs::directory_entry> dir_entries{} ;
	//fs::directory_iterator begin{currentPath} ;
	//fs::directory_iterator end{} ;
	//while(begin != end) {
	//	auto de = *begin++ ;
	//	std::cout << de.path().filename() << std::endl; 
	//}

	//Iterating with while is dangerous because it can have bugs, for example we forget to increment the iterator
	//It is better to use range based loop
	for(const auto & dir_entry : fs::directory_iterator{currentPath}) {
		dir_entries.push_back(dir_entry) ;
	}

	/*
	* std::partition reorders the vector based on the lambda, those which satisfy the condition goes first in the vector
	*/
	std::partition(dir_entries.begin(), dir_entries.end(), [](const fs::directory_entry & de) {
		return de.is_directory() ; //there are more function like this one
	}) ;

	//With this for and switch we iterate over currentPath without a specified order
	//for (const auto& dir_entry : fs::directory_iterator{currentPath}) {
		//switch (const auto& p = dir_entry.path();dir_entry.status().type()) {

	//With this for and switch we iterate first through directories
	//There are global functions of almost all functions used, like status in the switch below
	for(const auto &dir_entry : dir_entries) {
		//                                           local function          equivalent global function
		//                                            ^^^^^^                       ^^^^^^^^                        
		switch(const auto &p = dir_entry.path() ;/*dir_entry.status().type()*/ fs::status(p).type()) {
			//The switch returns a enum, whose types can be list in std::filesystem::file_type::
		case fs::file_type::directory:
			std::cout << "[DIR]\t" << p.string() << std::endl; 
			break ;
		case fs::file_type::regular: //file
			std::cout << '\t' << p.string() << '\t' << dir_entry.file_size() << std::endl; 
			break ;
		}
	}
}

void DirectoryOperations(std::string_view file) {
	fs::path currentPath{file} ;
	if(!fs::exists(currentPath)) { //directory exists
		std::cout << "Path does not exist = >" << currentPath.string() << std::endl ;
		return ;
	}
	currentPath /= "NewDir" ;
	//Maybe in functions create and remove an exception is thrown if an OS error happens. Better use try catch
	try {
		if(!fs::create_directory(currentPath)) { //Creating a directory
			std::cout << "Could not create a directory\n" ;
		}else {
			std::cout << "Directory created successfully\n" ;
		}
	
		if(!fs::remove(currentPath)) { //Removing a directory
			std::cout << "Could not delete the directory\n" ;
		}else {
			std::cout << "Directory removed successfully\n" ;
		}
	
		std::cout << fs::current_path() << std::endl; //gets the current path
		//We can change the current path, if it does not exist it will throw an exception
		std::cout << "Changing path\n";
		//There is a common pattern in filesystem functions. If we use it with std::error_code, there's no need of using try catch
		std::error_code ec{} ;
		fs::current_path(currentPath, ec); 
		if(ec) {
			std::cout << "Error:" << ec.message() << std::endl;
			return ;
		}
		std::cout << fs::current_path() << std::endl;
	}
	catch (std::exception& ex) {
		std::cout << "Exception:" << ex.what() << std::endl ;
	}
}

/*
* Permissions usually apply to owner, members of the owner groupand others.
* Windows, for example, is not this way, since the executable bit is always set to 1
*/
void demo_perms(fs::perms p)
{
    std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
              << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
              << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
              << '\n';
}
void Permissions(std::string_view file) {
	fs::path file_to_modify{file} ;
	if(!fs::exists(file_to_modify)) {
		std::cout << "Path does not exist = >" << file_to_modify.string() << std::endl ;
		return ;
	}
	auto perm = fs::status(file_to_modify).permissions() ;
	demo_perms(perm) ;
	std::cout << "Changing permissions\n" ;
	fs::permissions(file_to_modify,fs::perms::owner_write, fs::perm_options::add) ; //Add permission, obviously, there are more options in perms:: and fs::perm_options::
	perm = fs::status(file_to_modify).permissions() ;
	demo_perms(perm) ;
}
int main() {
	//DirectoryOperations(R"(E:\Data)") ;
	//TraversingDirectory(R"(E:\Data)") ;
	Permissions(R"(E:\Data\Launcher.cs)") ;
}

