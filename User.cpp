#include "User.h"
#include <fstream>
#include <nlohmann/json.hpp>

User::User(const std::string& username, const std::vector<unsigned char>& salt)
	: username(username), salt(salt) {
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