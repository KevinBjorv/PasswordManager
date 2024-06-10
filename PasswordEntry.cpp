#include "PasswordEntry.h"
PasswordEntry::PasswordEntry(const std::string& siteName, const std::string& username, const std::string& encryptedPassword, const std::string& entryNote)
	: siteName(siteName), username(username), encryptedPassword(encryptedPassword) , note(entryNote) {
}

std::string PasswordEntry::getSiteName() const {
	return siteName;
}

std::string PasswordEntry::getUsername() const {
	return username;
}

std::string PasswordEntry::getEncryptedPassword() const {
	return encryptedPassword;
}

void PasswordEntry::setSiteName(const std::string& sName) {
	siteName = sName;
}

void PasswordEntry::setUsername(const std::string& uName) {
	username = uName;
}

void PasswordEntry::setEncryptedPassword(const std::string& password) {
	encryptedPassword = password;
}

void PasswordEntry::setNote(const std::string& note) {
	this->note = note;
}

std::string PasswordEntry::getNote() const {
	return note;
}


// Path: PasswordEntry.cpp