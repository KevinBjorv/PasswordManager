#include "MenuManager.h"
#include "Dashboard.h"
#include "UtilityFunctions.h"
#include "ColorDefinitons.h"
#include <iostream>
#include <string>
#include <conio.h>

void MenuManager::displayMainMenu() {
	utility::setConsoleTitle("Password Manager - Main Menu");
	std::string choice;
	std::cout << ANSI_BOLD_HIGH_INTENSITY_BLUE << "Main Menu\n";
	std::cout << GREEN << "1. Log in\n";
	std::cout << PURPLE << "2. Register\n";
	std::cout << RED << "3. Exit\n";

	std::cout << ANSI_UNDERLINE_WHITE << "Enter choice:" << RESET << " ";
	std::cin >> choice;
	handleMainMenuChoice(choice);
}

void MenuManager::handleMainMenuChoice(std::string& rawChoice) {
	std::string choice = utility::convertToLowercase(rawChoice);
	if (choice == "1" || choice == "log in" || choice == "login") {
		std::cout << "\n";
		displayLogin();
	}
	else if (choice == "2" || choice == "register" || choice == "sign up") {
		std::cout << "\n";
		displayRegisterUser();
	}
	else if (choice == "3" || choice == "exit" || choice == "quit") {
		exit(0);
	}
	else {
		std::cout << RED << "Invalid choice - Please try again (Press any key to continue)" << RESET;
		char temp = _getch();
		utility::clearScreen();
		displayMainMenu();
	}
}

void MenuManager::displayRegisterUser() {
	utility::setConsoleTitle("Password Manager - Register");
	std::cout << ANSI_BOLD_HIGH_INTENSITY_BLUE << "Register user\n" << RESET;
	std::string newUsername;
	std::string newPassword;

	std::cout << "Enter username: ";
	std::cin >> newUsername;
	std::cout << "Enter password: ";
	std::cin >> newPassword;
	std::cin.clear();

	if (registerUser(newUsername, newPassword)) {
		std::cout << "Registration successful\n";
	}
	else {
		std::cout << RED << "Registration failed (Press any key to continue)" << RESET;
		char temp = _getch();
		utility::clearScreen();
		displayMainMenu();
	}
}

void MenuManager::displayLogin() {
	utility::setConsoleTitle("Password Manager - Log in");
	std::cout << ANSI_BOLD_HIGH_INTENSITY_BLUE << "Log in\n" << RESET;
	std::string username;
	std::string password;
	
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
		std::cerr << RED << "Log in failed, likely invalid credentials (Press any key to continue)" << RESET;
		char temp = _getch();
		utility::clearScreen();	
		displayMainMenu();
	}
}

// Path: MenuManager.cpp