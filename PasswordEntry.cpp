#include "PasswordEntry.h"
PasswordEntry::PasswordEntry(const std::string& siteName, const std::string& username, const std::string& password)
	: siteName(siteName), username(username), password(password) {
	
	// Constructor
}

std::string PasswordEntry::getSiteName() const {
	return siteName;
}

std::string PasswordEntry::getUsername() const {
	return username;
}

std::string PasswordEntry::getPassword() const {
	return password;
}