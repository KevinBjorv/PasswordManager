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
	std::string hashedPassword = hashPassword(userPassword);
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
	std::string hashedPassword = hashPassword(newUserPassword);
	currentUser = std::make_shared<User>(newUsername, hashedPassword);

	if (Database::saveUser(*currentUser)) {
		std::cout << "User registered successfully" << std::endl;
		return true;
	}
	else {
		std::cout << "User registration failed" << std::endl;
		currentUser.reset(); // Reset the shared pointer
		return false;
	}
}

void PasswordManager::addPasswordEntry() {
	if (!currentUser) {
		std::cout << "You need to log in to perform this action" << std::endl;
		return;
	}

	std::string siteName, username, password;
	std::cout << "Enter site name: ";
	std::cin >> siteName;
	std::cout << "Enter username: ";
	std::cin >> username;
	std::cout << "Enter password: ";
	std::cin >> password;

	PasswordEntry entry(siteName, username, password);
	currentUser->addPasswordEntry(entry);

	if (true){ // Temp debug
		std::cout << "Password entry added successfully" << std::endl;
	}
	else {
		std::cerr << "Error saving password entry" << std::endl;
	}
}

void PasswordManager::viewPasswordEntries() {
	if (!currentUser) {
		std::cout << "You need to log in first." << std::endl;
		return;
	}

	const auto& entries = currentUser->getPasswordEntries();
	for (const auto& entry : entries) {
		std::cout << "Site: " << entry.getSiteName() << ", Username: " << entry.getUsername() << ", Password: " << entry.getPassword() << std::endl;
	}
}

// Path: PasswordManager.cpp