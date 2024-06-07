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

void User::addPasswordEntry(const PasswordEntry& entry) {
	passwordEntries.push_back(entry);
}

const std::vector<PasswordEntry>& User::getPasswordEntries() const {
	return passwordEntries;
}

bool User::saveToFile() const {
	nlohmann::json j;
	j["username"] = username;
	j["passwordHash"] = passwordHash;
	j["passwordEntries"] = nlohmann::json::array();

	for (const auto& entry : passwordEntries) {
		nlohmann::json entryJson;
		entryJson["siteName"] = entry.getSiteName();
		entryJson["username"] = entry.getUsername();
		entryJson["password"] = entry.getPassword();
		j["passwordEntries"].push_back(entryJson);
	}

	std::ofstream file("data/" + username + ".json");
	if (!file.is_open()) {
		return false;
	}
	file << j.dump(4); // Pretty print with 4 spaces
	file.close();
	return true;
}

bool User::loadFromFile(const std::string& fileName) {
	std::ifstream file(fileName);
	if (!file.is_open()) {
		return false;
	}

	nlohmann::json j;
	file >> j;
	file.close();

	username = j["username"];
	passwordHash = j["passwordHash"];
	passwordEntries.clear();

	for (const auto& entryJson : j["passwordEntries"])  {
		PasswordEntry entry(entryJson["siteName"], entryJson["username"], entryJson["password"]);
		passwordEntries.push_back(entry);
	}
	
	return true;
}


// Path: User.cpp