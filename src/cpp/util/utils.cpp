#include "utils.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace Utils {
    std::vector<std::string> splitString(std::string startString, std::string delimiter)
    {
        size_t pos = 0;
        std::vector<std::string> tokens;
        // check if the delimiter is present and then add a substring to
        // the vector. finally erase the added part in the current string
        while ((pos = startString.find(delimiter)) != std::string::npos)
        {
            tokens.push_back(startString.substr(0, pos));
            startString.erase(0, pos + delimiter.length());
        }
        tokens.push_back(startString);
        return tokens;
    }

    // utility function
    std::string readStringFromFile(const char *filePath)
    {
        // convert file buffer to string stream and this
        // stream to a std::string
        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            file.open(filePath);
            std::stringstream fileStream;
            fileStream << file.rdbuf();
            file.close();
            return fileStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            return NULL;
        };
    }

    // loop through filesystem and get path entries
    // no recursion in subdirectories
    std::vector<std::string> getFilePathsInDirectory(std::string directorypath){
        std::vector<std::string> filepaths;
        for (const auto & entry : std::filesystem::directory_iterator(directorypath))
            filepaths.emplace_back(entry.path());
        return filepaths;
    }

    std::string getFileExtensionFromPath(std::string filepath){
        return std::filesystem::path(filepath).extension();
    }

    std::string getFileNameFromPath(std::string filepath){
        return std::filesystem::path(filepath).filename();
    }

    float froundf(float f)
    {
        return (float)floor(f + 0.5);
    }

    int froundi(float f)
    {
        return (int)floor(f + 0.5);
    }
}

