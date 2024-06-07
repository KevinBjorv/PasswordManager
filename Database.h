#pragma once

#include "User.h"
#include <memory>
#include <vector>

class PasswordEntry;

class Database {
public: 
	Database(); // Constructor
	~Database(); // Destructor

	void loadUsers();
	void saveUsers();
	void loadPasswordEntries();
	void savePasswordEntries();

	void addUser(std::shared_ptr<User> user);
	void addPasswordEntry(std::shared_ptr<PasswordEntry> passwordEntry);

	std::shared_ptr<User> findUser(const std::string& username);

private: 
	std::vector<std::shared_ptr<User>> users;
	std::vector<std::shared_ptr<PasswordEntry>> passwordEntries;
};