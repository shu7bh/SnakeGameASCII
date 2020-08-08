#include "Record.h"

Record::Record(const std::string& name, const Score& score)
	: name(name), Score(score), id(0) {}

Record::Record(const unsigned int& id, const Score& score)
	: id(id), Score(score), name("") {}

std::string Record::getName() const
{
	return name;
}

unsigned int Record::getId() const
{
	return id;
}

void Record::set(const std::string& name)
{
	this->name = name;
}

void Record::set(const unsigned int& id)
{
	this->id = id;
}
