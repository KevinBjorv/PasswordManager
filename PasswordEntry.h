#pragma once

#include <string>

class PasswordEntry {
public: 
	// Constructor
	PasswordEntry() = default;
	PasswordEntry(const std::string& siteName, const std::string& username, const std::string& encryptedPassword, const std::string& entryNote);

	// Destructor
	~PasswordEntry() = default;

	// Getters
	std::string getSiteName() const;
	std::string getUsername() const;
	std::string getEncryptedPassword() const;
	std::string getNote() const;
	
	// Setters
	void setSiteName(const std::string& siteName);
	void setUsername(const std::string& username);
	void setEncryptedPassword(const std::string& encryptedPassword);
	void setNote(const std::string& note);
private:
	// Password entry fields
	std::string siteName;
	std::string username;
	std::string encryptedPassword;
	std::string note;
};

// Path: PasswordEntry.h