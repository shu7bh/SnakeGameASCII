#pragma once

#include <map>
#include <vector>

#include "Food.h"

class Types
{
	const std::vector <Part> types;

	std::map <Coordinates, Food> food;

	unsigned int ct;
	
	float add;
	
	const float increaseAdd;

public: // Constructors

	Types() = default;

	Types(const decltype(types)&, const float&, const float&);

public: // Getters
	
	unsigned int getCt() const;

	float getAdd() const;

	const std::vector <Part>& getTypes() const;

	std::map <Coordinates, Food>& getFood(); // The food can change its value
	
public: // Setters or Modifiers

	void incrementCt();

	void decrementCt();

	void setAdd(float);

	void incrementAdd();

	void addFood();

	void initialize(float);
	
	virtual bool destroyIfEaten(const unsigned int&, const unsigned int&, bool&);
	
private:
	
	void addFood(int, int, int);

	void changeAdd();

};