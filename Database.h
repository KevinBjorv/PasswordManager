#pragma once

#include "Global.h"
#include <memory>
#include <vector>
#include <string>

// Forward declarations
class PasswordEntry;
class User;

class Database {
public: 
	Database(); // Constructor
	~Database(); // Destructor

	static bool saveUser(const User& user);
	static bool loadUser(User& user, const std::string& username);
	void loadPasswordEntries();
	void savePasswordEntries();

	void addUser(std::shared_ptr<User> user);
	void addPasswordEntry(std::shared_ptr<PasswordEntry> passwordEntry);

protected: 

private: 
	std::vector<std::shared_ptr<User>> users;
	std::vector<std::shared_ptr<PasswordEntry>> passwordEntries;
};

// Path: Database.h