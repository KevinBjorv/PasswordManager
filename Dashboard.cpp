#include "Dashboard.h"
#include "Encryption.h"
#include "ColorDefinitons.h"
#include <iostream>
#include "UtilityFunctions.h"
Dashboard::Dashboard(std::shared_ptr<User> currentUser)
	: currentUser(currentUser) {
	// Constructor
}

void Dashboard::open() {
    utility::setConsoleTitle("Password Manager - Dashboard");
    utility::clearScreen();

    std::string choice;
    while (true) {
        std::cout << ANSI_BOLD_HIGH_INTENSITY_BLUE << "Dashboard Menu\n" << RESET;
        std::cout << ANSI_HIGH_INTENSITY_CYAN << "1. View Passwords\n" << RESET;
        std::cout << ANSI_HIGH_INTENSITY_GREEN << "2. Add Password\n" << RESET;
        std::cout << ANSI_BOLD_HIGH_INTENSITY_RED << "3. Log out\n" << RESET;
        std::cout << ANSI_UNDERLINE_WHITE << "Enter choice: " << RESET;
        std::cin >> choice;

        if (choice == "1" || choice == "View passwords") {
            utility::clearScreen();
            viewPasswords();
        }
        else if (choice == "2" || choice == "Add password") {
			utility::clearScreen();
            addPassword();
        }
        else if (choice == "3" || choice == "Log out") {
            std::cout << RED << "Logging out...\n" << RESET;
            break;
        }
        else {
            std::cout << RED << "Invalid choice. Please try again.\n" << RESET;
            char temp = _getch();
        }
    }
}

void Dashboard::viewPasswords() {
    if (!currentUser) {
        std::cerr << RED << "User object is not valid. Please log in." << std::endl << RESET;
        return;
    }

    const auto& entries = currentUser->getPasswordEntries();
    if (entries.empty()) {
        std::cout << RED << "No passwords stored.\n" << RESET;
    }
    else {
        for (const auto& entry : entries) {
            std::string decryptedPassword = crypt::decrypt(entry.getEncryptedPassword(), currentUser->getPasswordHash(), currentUser->getSalt());
            std::cout << "Site: " << ANSI_BOLD_WHITE << entry.getSiteName() << RESET << ", Username: " << ANSI_BOLD_WHITE << entry.getUsername() << RESET << ", Password: " << ANSI_BOLD_WHITE << decryptedPassword << std::endl;
			char temp = _getch();
            utility::clearScreen();
        }
    }
}

void Dashboard::addPassword() {
    std::string siteName, username, password;
    std::cout << "Enter site name: ";
    std::cin >> siteName;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    std::string encryptedPassword = crypt::encrypt(password, currentUser->getPasswordHash(), currentUser->getSalt());

    PasswordEntry entry(siteName, username, encryptedPassword);
    currentUser->addPasswordEntry(entry);

    utility::clearScreen();

    if (Database::saveUser(*currentUser)) {
        std::cout << "Password entry added successfully\n";
    }
    else {
        std::cerr << RED << "Error saving password entry\n" << RESET;
    }
}

// Path: Dashboard.cpp