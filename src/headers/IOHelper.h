#pragma once
#include <iostream>
#include <sstream>
#include <string>

class IOHelper
{
public:
	static std::stringstream _warningBuffer;

	// Adds a new message to the Warning Buffer to be shown when trying to play a turn
	static void AddWarning(const std::string& message);

	// Function to display all messages in the warningBuffer
	static void ShowWarnings();

	// Clears the whole console
	static void Clear();

	// Grabs input for the whole line of command
	static void GetLine(std::string& input) {
		std::getline(std::cin, input);
	};

	// Adds a separation line to the console
	static void SeparationLine();

	// Convert each character in the string to lowercase
	static std::string ToLowerCase(const std::string& input);
};
