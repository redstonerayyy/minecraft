#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

//utility functions
std::vector<std::string> splitString(std::string startString, std::string delimiter);
std::string readStringFromFile(const char* filePath);

#endif