#include "UtilityFunctions.h"

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



}

// Path: UtilityFunctions.cpp