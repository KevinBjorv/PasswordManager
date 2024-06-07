#pragma once

#include <string>

class PasswordEntry {
public: 
	// Constructor
	PasswordEntry() = default;
	PasswordEntry(const std::string& siteName, const std::string& username, const std::string& password);

	// Destructor
	~PasswordEntry() = default;

	// Getters
	std::string getSiteName() const;
	std::string getUsername() const;
	std::string getPassword() const;

private:
	std::string siteName;
	std::string username;
	std::string password;
};
