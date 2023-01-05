#include "utils.hpp"

#include <vector>
#include <string>

namespace Utils {

std::vector<std::string> SplitString(std::string stringtosplit, std::string delimiter){
    size_t pos = 0;
    std::vector<std::string> parts;
    // check if the delimiter is present and then add a substring to
    // the vector. finally erase the added part in the current string
    while ((pos = stringtosplit.find(delimiter)) != std::string::npos)
    {
        parts.emplace_back(stringtosplit.substr(0, pos));
        stringtosplit.erase(0, pos + delimiter.length());
    }
    if(stringtosplit.length() > 0){
        parts.push_back(stringtosplit);
    }
    return parts;
}

}
