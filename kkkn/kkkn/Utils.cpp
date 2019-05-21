#include "Utils.h"
int CountLines(std::string file) {
	std::ifstream inp(file);
	std::string s;
	int count = 0;
	while (std::getline(inp, s))
		count++;
	return count;
}