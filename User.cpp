#include "User.h"
#include <fstream>
#include <nlohmann/json.hpp>

User::User(const std::string& username, const std::string& userPasswordHash) : username(username), passwordHash(userPasswordHash) {
	// Constructor
}

std::string User::getUsername() const {
	return username;
}

std::string User::getPasswordHash() const {
	return passwordHash;
}

void User::setUsername(const std::string& username) {
	this->username = username;
}

void User::setPasswordHash(const std::string& passwordHash) {
	this->passwordHash = passwordHash;
}


void User::addPasswordEntry(const PasswordEntry& entry) {
	passwordEntries.push_back(entry);
}

const std::vector<PasswordEntry>& User::getPasswordEntries() const {
	return passwordEntries;
}

// Path: User.cpp