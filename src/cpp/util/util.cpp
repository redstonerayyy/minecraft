#include "utils.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::string> splitString(std::string startString, std::string delimiter)
{
	size_t pos = 0;
	std::vector<std::string> tokens;
	while ((pos = startString.find(delimiter)) != std::string::npos)
	{
		tokens.push_back(startString.substr(0, pos));
		startString.erase(0, pos + delimiter.length());
	}
	tokens.push_back(startString);
	return tokens;
}

//utility function
std::string readStringFromFile(const char* filePath) {
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(filePath);
		std::stringstream fileStream;
		fileStream << file.rdbuf();
		file.close();
		return fileStream.str();

	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return NULL;
	};
}
