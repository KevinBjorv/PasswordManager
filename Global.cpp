#include "Global.h"
#include <Windows.h>

namespace global {
	std::string global::getBaseDirectory() {
		char buffer[MAX_PATH];
		GetModuleFileNameA(NULL, buffer, MAX_PATH);
		std::string fullPath(buffer);
		std::string::size_type pos = fullPath.find_last_of("\\/");

		// Remove the last directory (e.g, x64 or debug)
		fullPath = fullPath.substr(0, pos);
		pos = fullPath.find_last_of("\\/");

		// Remove the last directory (e.g, debug or PasswordManager)
		fullPath = fullPath.substr(0, pos);
		pos = fullPath.find_last_of("\\/");

		// Remove the last directory (e.g, PasswordManager)
		fullPath = fullPath.substr(0, pos);
		pos = fullPath.find_last_of("\\/");

		return fullPath; // Return the base directory
	}
}



// Path: Global.cpp