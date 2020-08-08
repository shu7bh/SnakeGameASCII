#include "Food.h"

Food::Food(const unsigned int& x, const unsigned int& y, const unsigned int& points, const char& shape,
	const int length)

	: Coordinates(x, y), Part(points, shape, length) {}

Food::Food(const Food& food)
	
	: Coordinates(food.getX(), food.getY()), Part(food.getPoints(), food.getShape()) {}

Food::Food(const Coordinates& coordinates, const Part& part)

	: Coordinates(coordinates), Part(part) {}
