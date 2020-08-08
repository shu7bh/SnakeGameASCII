#pragma once

class Coordinates
{
	unsigned int x, y;

public:

	Coordinates() = default;

	Coordinates(const unsigned int&, const unsigned int&);

	Coordinates(const Coordinates&);

public:

	unsigned int getX() const;

	unsigned int getY() const;

public:

	void setX(const unsigned int&);

	void setY(const unsigned int&);

	void set(const unsigned int&, const unsigned int&);

public:

	bool operator<(const Coordinates& rhs) const;
};