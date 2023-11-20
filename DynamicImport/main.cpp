#include <iostream>
#include <windows.h>

typedef void (*ReplaceStringFunc)(const char*, const char*);

int main()
{
	const HMODULE dll = LoadLibraryA("StringReplacer.dll");
	if (dll == nullptr)
		return 1;

	const auto replaceStringFunction = reinterpret_cast<ReplaceStringFunc>(GetProcAddress(dll, "ReplaceString"));

	if (replaceStringFunction == nullptr)
		return 1;

	const std::string test = "spring, summer";
	std::cout << test << std::endl;

	const std::string oldString = "spring";
	const std::string newString = "winter";

	replaceStringFunction(oldString.c_str(), newString.c_str());

	std::cout << test << std::endl;
	return 0;
}