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
	j["username"] = user.getUsernameHash();
	j["passwordHash"] = user.getPasswordHash();
	j["passwordEntries"] = nlohmann::json::array();
    for (const auto& entry : user.getPasswordEntries()) {
		nlohmann::json entryJson;
		entryJson["siteName"] = entry.getSiteName();
		entryJson["username"] = entry.getUsername();
		entryJson["password"] = crypt::base64Encode(entry.getEncryptedPassword()); // Encode to Base64

		j["passwordEntries"].push_back(entryJson);
    }
    std::string userFilePath = global.getBaseDirectory() + "/Resources/Users/" + user.getUsernameHash() + ".json";
	std::ofstream userFile(userFilePath);
	if (!userFile.is_open()) {
		return false;
	}
	userFile << j.dump(4); // Pretty print with 4 spaces
	userFile.close();
	return true;
}

bool Database::loadUser(User& user, const std::string& username) {
	Global global;
    std::string userFilePath = global.getBaseDirectory() + "/Resources/Users/" + username + ".json";
    std::ifstream userFile(userFilePath);
    if (!userFile.is_open()) return false;

    nlohmann::json j;
	userFile >> j;

	// Decode these from Base64 they were encoded
	std::cout << "Username: " << j["username"] << std::endl;
    user.setUsernameHash(j["username"]);
    user.setPasswordHash(j["passwordHash"]); 

    for (const auto& entryJson : j["passwordEntries"]) {
        PasswordEntry entry(entryJson["siteName"], entryJson["username"], crypt::base64Decode(entryJson["password"]));
        user.addPasswordEntry(entry);
    }
	userFile.close();
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
