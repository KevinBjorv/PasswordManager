#pragma once

#include <string>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <codecvt>
#include <locale>

namespace utility {
	void setConsoleTitle(const std::string& title);
	
	void clearScreen();
}

//Path: UtilityFunctions.h