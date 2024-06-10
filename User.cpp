#include "User.h"
#include <fstream>
#include <nlohmann/json.hpp>

User::User(const std::string& username, const std::vector<unsigned char>& salt)
	: usernameHash(usernameHash), salt(salt) {
	// Constructor implementation, possibly initialize other members or perform actions.
}
void User::generateSalt(size_t length) {
	salt.resize(length);
	RAND_bytes(salt.data(), length);
}

std::vector<unsigned char> User::getSalt() const {
	return salt;
}

void User::setSalt(const std::vector<unsigned char>& newSalt) {
	salt = newSalt;
}

std::string User::getUsernameHash() const {
	return usernameHash;
}

std::string User::getPasswordHash() const {
	return passwordHash;
}

void User::setUsernameHash(const std::string& username) {
	usernameHash = username;
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