#pragma once

#pragma once
#include <string>
#include "Score.h"

class Record : public Score
{
	std::string name;
	unsigned int id;

public:

	Record(const std::string& name, const Score& score);

	Record(const unsigned int& id, const Score& score);

	std::string getName() const;

	unsigned int getId() const;

	void set(const std::string&);

	void set(const unsigned int&);
};