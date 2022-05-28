#include <vector>

std::vector<std::string> splitString(std::string startString, std::string delimiter){
	size_t pos = 0;
	std::vector<std::string> tokens;
	while ((pos = startString.find(delimiter)) != std::string::npos) {
		tokens.push_back(startString.substr(0, pos));
		startString.erase(0, pos + delimiter.length());
	}
	tokens.push_back(startString);
	return tokens;	
}
