#pragma once

#include "PasswordManager.h"

class Dashboard; // Forward declaration

class MenuManager : public PasswordManager { // Display menu related to PasswordManager
public:
	void displayMainMenu(); // Returns the choice

	// Login/Register
	void displayLogin();
	void displayRegisterUser();

private: 
	void handleMainMenuChoice(std::string& choice); // Converts text choice to int
};

// MenuManger.h

