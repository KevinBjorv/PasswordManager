#pragma once

#include "PasswordManager.h"

#include "Dashboard.h"
class MenuManager : public PasswordManager { // Display menu related to PasswordManager
public:
	void displayMainMenu(); // Returns the choice

	// Login/Register
	void displayLogin();
	void displayRegisterUser();

private: 
	void handleMainMenuChoice(std::string& choice); // Converts text choice to int
	Dashboard* dashboard(std::shared_ptr<User> currentUser); // Display dashboard when user is logged in
};

