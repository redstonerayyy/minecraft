#pragma once

#include <vector>
#include <string>
#include "math.h"

namespace Utils
{
    // utility functions
    // string
    std::vector<std::string> splitString(std::string startString, std::string delimiter);
    // file
    std::string readStringFromFile(const char *filePath);
    std::vector<std::string> getFilePathsInDirectory(std::string directorypath);
    std::string getFileExtensionFromPath(std::string filepath);
    std::string getFileNameFromPath(std::string filepath);
    // numbers
    float froundf(float f);
    int froundi(float f);
}
