#include "GlobalAndConstants.h"
#include <algorithm>
#include <map>

char Snake::shape = 'o';

Snake::Snake(const char& nextDir, const unsigned int& x, const unsigned int& y)
	: curDir(nextDir), nextDir(nextDir), Coordinates(x, y)
{
	GAME::Field[x][y] = shape;
}

bool Snake::MoveIfFree(const unsigned int& x, const unsigned int& y, bool& flag, bool& addAtEnd)
{			// Will move the snake if the 
	if (GAME::Field[x][y] == GAME::FREE)
		//if (!flag)
	{
		std::swap(GAME::Field[x][y], GAME::Field[getX()][getY()]);
		set(x, y);
		return true;
	}
		
	if (!FOOD::normal.destroyIfEaten(x, y, addAtEnd) 
		&& !FOOD::booster.destroyIfEaten(x, y, addAtEnd))
		return false;
	
	flag = true;

	GAME::Field[x][y] = shape;
	GAME::Field[getX()][getY()] = GAME::FREE;

	set(x, y);

	return false;
}

bool Snake::move(bool& flag, bool& addAtEnd)
{
	curDir = nextDir;

	switch (curDir)
	{
	case MOVE::UP:
		if (!MoveIfFree(getX() - 1, getY(), flag, addAtEnd))	// Will return false if the
			return false;	// object part encounters anything in its way

		break;

	case MOVE::DOWN:
		if (!MoveIfFree(getX() + 1, getY(), flag, addAtEnd))
			return false;

		break;

	case MOVE::LEFT:
		if (!MoveIfFree(getX(), getY() - 1, flag, addAtEnd))
			return false;

		break;

	case MOVE::RIGHT:
		if (!MoveIfFree(getX(), getY() + 1, flag, addAtEnd))
			return false;

		break;

	default:
		break;
	}
	return true;
}

char Snake::getDir() const
{
	return curDir;
}

char Snake::getShape()
{
	return shape;
}

void Snake::setNextDir(const char nextDir)
{
	this->nextDir = nextDir;
}