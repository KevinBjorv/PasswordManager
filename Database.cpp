#include "Database.h"
#include "PasswordEntry.h"
#include <fstream>

Database::Database() {
	// Constructor
}

Database::~Database() {
	// Destructor
}

void Database::loadUsers() {
    // Implementation for loading users from a file
}

void Database::saveUsers() {
    // Implementation for saving users to a file
}

void Database::loadPasswordEntries() {
    // Implementation for loading password entries from a file
}

void Database::savePasswordEntries() {
    // Implementation for saving password entries to a file
}

void Database::addUser(std::shared_ptr<User> user) {
    users.push_back(user);
}

void Database::addPasswordEntry(std::shared_ptr<PasswordEntry> entry) {
    passwordEntries.push_back(entry);
}

std::shared_ptr<User> Database::findUser(const std::string& username) {
    for (auto& user : users) {
        if (user->getUsername() == username) {
            return user;
        }
    }
    return nullptr;
}