#pragma once
#include "PasswordManager.h"
#include "User.h"

class Dashboard : public PasswordManager { // Display dashboard when user is logged in
public: // Make protected
	Dashboard(std::shared_ptr<User> currentUser);

	// Display Dashboard
	void open();

private:
	// Current user
	std::shared_ptr<User> currentUser;

	// Menu options
	void addPassword();
	void viewPasswords();
	void openGeneratePasswordMenu();

	std::string generatePassword(int length = 16, bool includeSpecialChars = true, bool includeUppercase = true, bool includeNumbers = true); // 0 length = random
};

// Path: Dashboard.h