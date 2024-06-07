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
	bool login(const std::string& username, std::string& userPassword);
	bool registerUser(const std::string& newUsername, std::string& newUserPassword);

	// PasswordEntry methods
	void addPasswordEntry();
	void viewPasswordEntries();

	// Class objects
	std::shared_ptr<Database> database;
	std::shared_ptr<User> currentUser;
};

