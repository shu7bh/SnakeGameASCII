#include "Part.h"
#include "GlobalAndConstants.h"

Part::Part(const int& points, const char& shape, const int length)
	: points(points), shape(shape), length(length) {}

Part::Part(const Part& part) : points(part.points), shape(part.shape), length(part.length) {}

int Part::getPoints() const
{
	return points;
}

char Part::getShape() const
{
	return shape;
}

int Part::getLength() const
{
	return length;
}

void Part::set(const int& points)
{
	this->points = points;
}

void Part::set(const char& shape)
{
	this->shape = shape;
}

void Part::setLength(const int length)
{
	this->length = length;
}

void Part::set(const int& points, const char& shape, const int length)
{
	this->points = points;
	this->shape = shape;
	this->length = length;
}

bool Part::changeSnakelength()
{
	if (length == 1)
		return true;

	if (length < 0)
		for (int i = 0; i > length; i--)
		{
			if (GAME::snake.size() <= 1)
				return false;

			GAME::Field[GAME::snake.back().getX()][GAME::snake.back().getY()] = GAME::FREE;
			GAME::snake.pop_back();
		}

	return false;
}