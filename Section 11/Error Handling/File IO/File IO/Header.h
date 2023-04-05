/*
* iostream: console input/output
* fstream: file input/output
* stringstream (or sstream): buffer input/output
*/
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

class Test {
	std::fstream fstream;
	std::ifstream ifstream;
	std::ofstream ofstream;
	std::istringstream istringstream;
	std::ostringstream ostringstream;
	std::stringstream str;
};