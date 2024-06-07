#include "MenuManager.h"
#include "Dashboard.h"
#include <iostream>
#include <string>

void MenuManager::displayMainMenu() {
	std::string choice;
	std::cout << "Main Menu" << std::endl;
	std::cout << "1. Login" << std::endl;
	std::cout << "2. Register" << std::endl;
	std::cout << "3. Exit" << std::endl;

	std::cout << "Enter choice: ";
	std::cin >> choice;
	handleMainMenuChoice(choice);
}

void MenuManager::handleMainMenuChoice(std::string& choice) {
	if (choice == "Login" || choice == "login" || choice == "1") {
		displayLogin();
	}
	else if (choice == "Register" || choice == "register" || choice == "2") {
		displayRegisterUser();
	}
	else if (choice == "Exit" || choice == "exit" || choice == "3") {
		exit(0);
	}
	else {
		std::cout << "Invalid choice. Please try again." << std::endl;
	}
}

void MenuManager::displayRegisterUser() {
	std::string newUsername;
	std::string newPassword;
	
	std::cout << "Register" << std::endl;

	std::cout << "Enter username: ";
	std::cin >> newUsername;
	std::cout << "Enter password: ";
	std::cin >> newPassword;

	if (registerUser(newUsername, newPassword)) {
		std::cout << "Registration successful" << std::endl;
	}
	else {
		std::cout << "Registration failed" << std::endl;
	}
}

void MenuManager::displayLogin() {
	std::string username;
	std::string password;
	
	std::cout << "Login" << std::endl;

	std::cout << "Enter username: ";
	std::cin >> username;
	std::cout << "Enter password: ";
	std::cin >> password;
	

	std::shared_ptr<User> user = login(username, password);
	if (user) {
		Dashboard dashboard(user);
		dashboard.open();
	}
	else {
		std::cerr << "Login failed: User can not be null pointer" << std::endl;
	}
}

// Path: MenuManager.cpp