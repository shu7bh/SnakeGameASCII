#include "Coordinates.h"

Coordinates::Coordinates(const unsigned int& x, const unsigned int& y)
	: x(x), y(y) {}

Coordinates::Coordinates(const Coordinates& copy)
{
	x = copy.x;
	y = copy.y;
}

unsigned int Coordinates::getX() const
{
	return x;
}

unsigned int Coordinates::getY() const
{
	return y;
}

void Coordinates::setX(const unsigned int& x)
{
	this->x = x;
}

void Coordinates::setY(const unsigned int& y)
{
	this->y = y;
}

void Coordinates::set(const unsigned int& x, const unsigned int& y)
{
	setX(x);
	setY(y);
}

bool Coordinates::operator<(const Coordinates& rhs) const
{
	if (x < rhs.x)
		return true;
	if (x > rhs.x)
		return false;
	if (y > rhs.y)
		return false;
	return true;
}
