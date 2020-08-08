#include "Types.h"
#include <random>
#include "GlobalAndConstants.h"

Types::Types(const decltype(types)& types, const float& add, const float& increaseAdd)

	: types(types), ct(0), add(add), increaseAdd(increaseAdd) {}

unsigned int Types::getCt() const
{
	return ct;
}

float Types::getAdd() const
{
	return add;
}

const std::vector <Part>& Types::getTypes() const
{
	return types;
}

std::map <Coordinates, Food>& Types::getFood()
{
	return food;
}

void Types::incrementCt()
{
	ct++;
}

void Types::decrementCt()
{
	ct--;
}

void Types::setAdd(float add)
{
	this->add = add;
}

void Types::incrementAdd()
{
	add += increaseAdd;
}

void Types::addFood(int r, int c, int val)
{
	this->food[Coordinates(r, c)] = 
		Food( r, c, types[val].getPoints(), types[val].getShape(), types[val].getLength() );
}

void Types::changeAdd()
{
	if (food.begin()->second.getLength() == 1)
		return;

	add = 0.5f;
}

void Types::addFood()
// To create normalFood if the normalFood has been eaten
{
	std::default_random_engine R(static_cast<unsigned int>(time(0)));

	std::uniform_int_distribution <unsigned int> range
	(0, types.size() - 1);
	// For the no of normalFood types

	std::uniform_int_distribution <unsigned int> row(2, GAME::Field.size() - 2);
	std::uniform_int_distribution <unsigned int>
		col(2, GAME::Field.begin()->size() - 2);

	incrementAdd();

	while (ct <	unsigned int(add))
	{
		incrementCt();
		unsigned int val = range(R);
		unsigned int r, c;
		do				// The loop wil run until it satisfies the given condition
			r = row(R), c = col(R);
		while (GAME::Field[r][c] != GAME::FREE);

		addFood(r, c, val);

		GAME::Field[r][c] = types[val].getShape();

		changeAdd();
	}
}

void Types::initialize(float add)
{
	this->add = add;
	ct = 0;
	food.clear();
}

bool Types::destroyIfEaten(const unsigned int& x, const unsigned int& y, bool& addAtEnd)
{
	std::map <Coordinates, Food>::iterator it;

	for (it = food.begin(); it != food.end(); it++)
		if (it->first.getX() == x && it->first.getY() == y)
		{
			GAME::points += it->second.getPoints();
			ct--;
			addAtEnd = it->second.changeSnakelength();
			food.erase(it);	// erase needs an iterator

			return true;
		}

	return false;
}