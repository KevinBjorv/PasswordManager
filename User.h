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

	void addPasswordEntry(const PasswordEntry& entry);
	
	bool saveToFile() const;
	bool loadFromFile(const std::string& fileName);


private: 
	std::string username;
	std::string passwordHash;
	std::vector<PasswordEntry> passwordEntries;
};