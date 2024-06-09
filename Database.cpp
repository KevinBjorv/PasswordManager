#include "Database.h"
#include "PasswordEntry.h"
#include "User.h"
#include "Encryption.h"
#include "Global.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

Database::Database() {
	// Constructor
}

Database::~Database() {
	// Destructor
}

bool Database::saveUser(const User& user) {
	Global global;
	nlohmann::json j;
	j["username"] = user.getUsername();
	j["passwordHash"] = user.getPasswordHash();
	j["passwordEntries"] = nlohmann::json::array();
    for (const auto& entry : user.getPasswordEntries()) {
		nlohmann::json entryJson;
		entryJson["siteName"] = entry.getSiteName();
		entryJson["username"] = entry.getUsername();
		entryJson["password"] = entry.getEncryptedPassword();
		j["passwordEntries"].push_back(entryJson);
    }
    std::string userDirectory = global.getBaseDirectory() + "/Resources/Users/" + user.getUsername() + ".json";
	std::ofstream file(userDirectory);
	if (!file.is_open()) {
		return false;
	}
	file << j.dump(4); // Pretty print with 4 spaces
	file.close();
	return true;
}

bool Database::loadUser(User& user, const std::string& username) {
	Global global;
	std::string filePath = global.getBaseDirectory() + "/Resources/Users/" + username + ".json";
	std::ifstream file(filePath);
	if (!file.is_open()) return false;

	nlohmann::json j;
	file >> j;

	user.setUsername(j["username"]); 
	user.setPasswordHash(j["passwordHash"]);
	//user.clearPasswordEntries(); // Clear any existing password entries

	for (const auto& entryJson : j["passwordEntries"]) {
		PasswordEntry entry(entryJson["siteName"], entryJson["username"], entryJson["password"]);
		user.addPasswordEntry(entry);
	}
	file.close();
	return true;
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

// Path: Database.cpp
