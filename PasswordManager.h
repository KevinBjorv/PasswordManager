#pragma once

#include "user.h"
#include "PasswordEntry.h"
#include "Database.h"
#include <memory>

class PasswordManager {
public:
	PasswordManager(); // Constructor
	~PasswordManager(); // Destructor

	void run();
protected: 
	// User methods - Returns true if successful
	std::shared_ptr<User> login(const std::string& username, std::string& userPassword);
	bool registerUser(const std::string& newUsername, const std::string& newUserPassword);

	// Class objects
	std::shared_ptr<Database> database;
	std::shared_ptr<User> currentUser;

private: 
	// Return true if successful
	bool validateUsername(const std::string& username, const std::string& usernameHash);
	bool validatePassword(const std::string& password);

	// Return true if unique
	bool isUsernameUnique(const std::string& usernameHash);
};

// Path: PasswordManager.h