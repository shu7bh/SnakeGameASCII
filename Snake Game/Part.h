#pragma once

class Part
{
	int points;
	char shape;
	int length;

public:

	Part(const int&, const char&, const int length = 1);

	Part(const Part&);

	Part() = default;

public:

	int getPoints() const;

	char getShape() const;

	int getLength() const;

public:

	void set(const int&);

	void set(const char&);

	void setLength(const int);

	void set(const int&, const char&, const int length = 1);
	
	bool changeSnakelength();
};