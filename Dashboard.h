#pragma once
#include "PasswordManager.h"
#include "User.h"

class Dashboard : public PasswordManager { // Display dashboard when user is logged in
protected:
	Dashboard(std::shared_ptr<User> currentUser);

	// Display Dashboard
	void open();


private:
	std::shared_ptr<User> currentUser;

	// Menu options


};