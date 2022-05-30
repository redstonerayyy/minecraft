#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

std::vector<std::string> splitString(std::string startString, std::string delimiter);

//utility function
std::string readStringFromFile(const char* filePath);

#endif