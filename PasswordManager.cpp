#include <iostream>
#include "PasswordManager.h"
#include "MenuManager.h"
#include "Encryption.h"
#include "Global.h"
#include <nlohmann/json.hpp>
#include <filesystem>
#include "ColorDefinitons.h"
namespace fs = std::filesystem;

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
	std::string hashedUsername = crypt::hashPassword(username);
	currentUser = std::make_shared<User>();

	if (Database::loadUser(*currentUser, hashedUsername) && currentUser->getPasswordHash() == hashedPassword && currentUser->getUsernameHash() == hashedUsername) {
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
	std::vector<unsigned char> salt;
	currentUser = std::make_shared<User>(newUsername, salt);
	currentUser->generateSalt();
	std::string passwordHash = crypt::hashPassword(newUserPassword); 
	currentUser->setPasswordHash(passwordHash);
	std::string usernameHash = crypt::hashPassword(newUsername);
	currentUser->setUsernameHash(usernameHash);

	if (validateUsername(newUsername, usernameHash) && validatePassword(newUserPassword)) {
		if (Database::saveUser(*currentUser)) {
			std::cout << "User registered successfully" << std::endl;
			return true;
		}
		else {
			std::cerr << "Failed to save user to database" << std::endl;
			currentUser.reset();
			return false;
		}
	}
	else {
		return false;
	}
}

bool PasswordManager::validateUsername(const std::string& username, const std::string& usernameHash) {
	if (username.length() <= 3) {
		std::cout << "Username must be longer than 3 characters\n";
		return false;
	} else if (username.length() >= 25) {
		std::cout << "Username must be shorter than 25 characters\n";
		return false;
	} else if (username.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != std::string::npos) {
		std::cout << "Username must only contain alphanumeric characters\n";
		return false;
	}
	// Check if username is unique in resource folder
	if (isUsernameUnique(usernameHash)) {
		return true;
	} else {
		std::cout << "Username is already taken\n";
		return false;
	}
} 

bool PasswordManager::validatePassword(const std::string& password) {
	if (password.length() <= 8) {
		std::cout << "Password must be longer than 8 characters\n";
		return false;
	} else if (password.length() >= 50) {
		std::cout << "Are you sure you want your password to be " << password.length() << " characters long? (y/n)\n";
		std::string input; std::cin >> input;
		if (input == "y" || input == "yes") {
			return true;
		} else {
			return false;
		}
	} else if (password.length() >= 150) {
		std::cout << "Password can not be more than 150 characters long\n";
		return false;
	}
	return true;
}

bool PasswordManager::isUsernameUnique(const std::string& usernameHash) {
	std::string userDirectory = global::getBaseDirectory() + "/Resources/Users";
	for (const auto& entry : fs::directory_iterator(userDirectory)) {
		if (entry.is_regular_file()) {
			std::string filename = entry.path().stem().string();
			// Extract the filename without extension
			if (filename == usernameHash) {
				return false; // Username is not unique
			}
		}
	}
	return true; // Username is unique
}

// Path: PasswordManager.cpp