#pragma once
#include "Coordinates.h"
#include "Part.h"

class Food : public Coordinates, public Part
{

public:

	Food() = default;

	Food(const unsigned int&, const unsigned int&, const unsigned int&, const char&,
		const int length = 1);

	Food(const Food&);

	Food(const Coordinates&, const Part&);
};