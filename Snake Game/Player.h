#pragma once
#include <vector>
#include <string>
#include "Score.h"

class Player
{
	std::string username, password;

public:

	std::vector <Score> score;

public:

	// *********************** Constructors Here **************************

	Player();

	Player(const std::string& username, const std::string& password);

	// ********************* Getter Functions Here *************************

	std::string getUsername() const;

	std::string getPassword() const;

	// ********************* Setter Functions Here *************************

	void setUsername(const std::string& username);

	void setPassword(const std::string& password);

	// *************** Operator Overloaded Functions Here *******************

	friend std::ifstream& operator>>(std::ifstream&, Player&);

	friend std::ofstream& operator<<(std::ofstream&, const Player&);
};

