#include "UtilityFunctions.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <codecvt>
#include <locale>
#include <algorithm>
#include <cctype>

namespace utility{

	void utility::setConsoleTitle(const std::string& title) {
		#if defined(_WIN32) || defined(_WIN64)
				// Determine the size of the wide string
				int wideSize = MultiByteToWideChar(CP_UTF8, 0, title.c_str(), -1, nullptr, 0);
				std::wstring wideTitle(wideSize, 0);

				// Convert the UTF-8 string to a wide string
				MultiByteToWideChar(CP_UTF8, 0, title.c_str(), -1, &wideTitle[0], wideSize);

				// Use the wide string with the Windows API
				SetConsoleTitle(wideTitle.c_str());
		#endif
	}

	void utility::clearScreen() {
		#if defined(_WIN32) || defined(_WIN64)
				system("cls");
		#elif defined(__linux__) || defined(__APPLE__)
				system("clear");
		#else 
				std::cerr << "Unsupported Console/OS" << endl;
		#endif
	}

	std::string utility::convertToLowercase(const std::string& str) {
		std::string lowercaseStr = str;  // Create a copy of the input string to transform

		// Transform each character to lowercase
		std::transform(lowercaseStr.begin(), lowercaseStr.end(), lowercaseStr.begin(),
			[](unsigned char c) -> char { return std::tolower(c); });

		return lowercaseStr;  // Return the transformed string
	}
}

// Path: UtilityFunctions.cpp