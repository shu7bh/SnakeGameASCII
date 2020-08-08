#include "Player.h"

Player::Player() {}

Player::Player(const std::string& username, const std::string& password)
	: username(username), password(password) {}

std::string Player::getUsername() const
{
	return username;
}

std::string Player::getPassword() const
{
	return password;
}

void Player::setUsername(const std::string& username)
{
	this->username = username;
}

void Player::setPassword(const std::string& password)
{
	this->password = password;
}
