#include "Dashboard.h"
#include "Encryption.h"
#include <iostream>

Dashboard::Dashboard(std::shared_ptr<User> currentUser)
	: currentUser(currentUser) {
	// Constructor
}

void Dashboard::open() {
    std::string choice;
    while (true) {
        std::cout << "Dashboard Menu\n";
        std::cout << "1. View Passwords\n";
        std::cout << "2. Add Password\n";
        std::cout << "3. Logout\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == "1") {
            viewPasswords();
        }
        else if (choice == "2") {
            addPassword();
        }
        else if (choice == "3") {
            std::cout << "Logging out...\n";
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Dashboard::viewPasswords() {
    if (!currentUser) {
        std::cout << "User object is not valid. Please log in." << std::endl;
        return;
    }

    const auto& entries = currentUser->getPasswordEntries();
    if (entries.empty()) {
        std::cout << "No passwords stored.\n";
    }
    else {
        for (const auto& entry : entries) {
            std::string decryptedPassword = crypt::decrypt(entry.getEncryptedPassword(), currentUser->getPasswordHash(), currentUser->getSalt());
            std::cout << "Site: " << entry.getSiteName() << ", Username: " << entry.getUsername() << ", Password: " << decryptedPassword << std::endl;
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

    if (Database::saveUser(*currentUser)) {
        std::cout << "Password entry added successfully.\n";
    }
    else {
        std::cout << "Error saving password entry.\n";
    }
}

// Path: Dashboard.cpp