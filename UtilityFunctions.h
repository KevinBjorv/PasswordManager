#pragma once

#include <string>

namespace utility {
	void setConsoleTitle(const std::string& title);
	
	void clearScreen();

	std::string convertToLowercase(const std::string& str);
}

//Path: UtilityFunctions.h