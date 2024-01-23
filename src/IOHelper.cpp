#include "./headers/IOHelper.h"
#include <conio.h>
#include <iostream>

// Definition of the warningBuffer
std::stringstream IOHelper::_warningBuffer;

void IOHelper::AddWarning(const std::string& message)
{
	_warningBuffer << message << std::endl;
}

void IOHelper::ShowWarnings() {
	if (_warningBuffer.str() != "") 
		std::cout << "Warnings:" << std::endl;

	std::cout << _warningBuffer.str() << std::endl;
	_warningBuffer.str("");
}

void IOHelper::Clear()
{
	system("cls");
}

void IOHelper::SeparationLine()
{
	std::cout << "--------------------------" << std::endl;
}

std::string IOHelper::ToLowerCase(const std::string& input)
{
	std::string result = input;
	for (char& c : result) {
		c = std::tolower(c);
	}
	return result;
}