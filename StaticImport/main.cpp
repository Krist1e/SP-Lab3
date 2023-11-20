#include <iostream>
#include <string>

#include "StringReplacer.h"

int main()
{
	const std::string test = "spring, winter";
	std::cout << test << std::endl;

	const std::string oldString = "spring";
	const std::string newString = "summer";

	ReplaceString(oldString.c_str(), newString.c_str());

	std::cout << test << std::endl;
	return 0;
}
