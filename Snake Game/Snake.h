#pragma once
#include "Coordinates.h"
#include <map>
#include "Food.h"

class Snake : public Coordinates
{
	char curDir, nextDir;

	static char shape;

private:

	bool MoveIfFree(const unsigned int&, const unsigned int&, bool&, bool&);
	
public:

	Snake(const char&, const unsigned int&, const unsigned int&);

public:

	bool move(bool&, bool&);

public:

	char getDir() const; // Function which will return the current 
	// dir of the snake part so as to initialize it to the nextDir part following it

public:

	static char getShape();

public:

	void setNextDir(const char nextDir);
};