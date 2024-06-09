#include <iostream>
#include "PasswordManager.h"
#include "MenuManager.h"
#include "Encryption.h"
#include <nlohmann/json.hpp>
// Constructor
PasswordManager::PasswordManager() : database(std::make_shared<Database>()){}

// Destructor
PasswordManager::~PasswordManager(){	
}

void PasswordManager::run() {
	MenuManager menu;
	menu.displayMainMenu();
}

std::shared_ptr<User> PasswordManager::login(const std::string& username, std::string& userPassword) {
	std::string hashedPassword = crypt::hashPassword(userPassword);
	currentUser = std::make_shared<User>();

	if (Database::loadUser(*currentUser, username) && currentUser->getPasswordHash() == hashedPassword) { 
		std::cout << "Login successful" << std::endl;
		if (currentUser) {
			return currentUser; // Return the shared pointer
		}
		else {
			std::cerr << "User was nullptr" << std::endl;
			return nullptr;
		}
	}
	else {
		currentUser.reset(); // Reset the shared pointer
		return nullptr; // Error message will be displayed in MenuManager
	}
}

bool PasswordManager::registerUser(const std::string& newUsername, const std::string& newUserPassword) {
	currentUser = std::make_shared<User>(newUsername);
	currentUser->generateSalt();  // Ensure this method exists and correctly generates and stores a salt
	std::string encryptedPassword = crypt::encrypt(newUserPassword, newUserPassword, currentUser->getSalt());  // Using the password itself as the secret here for simplicity

	if (Database::saveUser(*currentUser)) {
		std::cout << "User registered successfully" << std::endl;
		return true;
	}
	else {
		std::cout << "User registration failed" << std::endl;
		currentUser.reset();
		return false;
	}
}


// Path: PasswordManager.cpp