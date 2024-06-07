#pragma once
#include <string>
#include <vector>
#include "PasswordEntry.h"

class User {
public: 
	User() = default;
	User(const std::string& username, const std::string& userPasswordHash);
	
	~User() = default;

	// Getters
	std::string getUsername() const;
	std::string getPasswordHash() const;
	const std::vector<PasswordEntry>& getPasswordEntries() const;

	// Setters
	void setUsername(const std::string& username);
	void setPasswordHash(const std::string& passwordHash);

	// Add password entry
	void addPasswordEntry(const PasswordEntry& entry);
private: 
	std::string username;
	std::string passwordHash;
	std::vector<PasswordEntry> passwordEntries;
};