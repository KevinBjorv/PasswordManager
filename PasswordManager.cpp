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

bool PasswordManager::login(const std::string& username, std::string& userPassword) {
	std::string hashedPassword = hashPassword(userPassword);
	std::string fileName = "data/" + username + ".json";

	currentUser = std::make_shared<User>();
	if (currentUser->loadFromFile(fileName) && currentUser->getPasswordHash() == hashedPassword) {
		std::cout << "Login successful" << std::endl;
		return true;
	}
	else {
		std::cout << "Login failed" << std::endl;
		currentUser.reset();
		return false;
	}
}

bool PasswordManager::registerUser(const std::string& newUsername, std::string& newUserPassword) {
	std::string hashedPassword = hashPassword(newUserPassword);
	std::cout << "Hashed password: " << hashedPassword << std::endl; // Debugging

	if (currentUser->saveToFile()) {
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

	if (currentUser->saveToFile()){
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