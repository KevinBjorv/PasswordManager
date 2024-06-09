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
};

// Path: Dashboard.h