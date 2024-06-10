#pragma once
#include <string>
#include <vector>
#include "PasswordEntry.h"
#include "Encryption.h"

class User {
public: 
	User() = default;
	User(const std::string& username, const std::vector<unsigned char>& salt);
	
	~User() = default;

	// Getters
	std::string getUsernameHash() const;
	std::string getPasswordHash() const;
	const std::vector<PasswordEntry>& getPasswordEntries() const;
	std::vector<unsigned char> getSalt() const;

	// Setters
	void setUsernameHash(const std::string& username);
	void setPasswordHash(const std::string& passwordHash);
	void setSalt(const std::vector<unsigned char>& newSalt);

	// Add password entry
	void addPasswordEntry(const PasswordEntry& entry);

	// Generate a new salt
	void generateSalt(size_t length = 16);
private: 
	std::string usernameHash;
	std::string passwordHash;
	std::vector<PasswordEntry> passwordEntries;
	std::vector<unsigned char> salt;
};

// Path: User.h