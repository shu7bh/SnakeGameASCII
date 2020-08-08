#include "Score.h"
#include <fstream>

// Constructors

Score::Score(const Score& score)

	: points(score.getPoints()), length(score.getLength()), moves(score.getMoves()),
	id(score.getId()), duration(score.getDuration())  {}

Score::Score(const unsigned int& id, const unsigned int& points, const unsigned int& length, const unsigned int& moves, const int& duration)

	: id(id), points(points), length(length), moves(moves), duration(duration) {}

Score::Score(const unsigned int& points, const unsigned int& length, const unsigned int& moves, const int& duration)

	: id(0), points(points), length(length), moves(moves), duration(duration) {}


// Getter Functions

unsigned int Score::getId() const
{
	return id;
}

unsigned int Score::getPoints() const
{
	return points;
}

unsigned int Score::getLength() const
{
	return length;
}

int Score::getDuration() const
{
	return duration;
}

unsigned int Score::getMoves() const
{
	return moves;
}



// Setter Functions

void Score::setId(const unsigned int& id)
{
	this->id = id;
}

void Score::setPoints(const unsigned int& points)
{
	this->points = points;
}

void Score::setLength(const unsigned int& length)
{
	this->length = length;
}

void Score::setDuration(const int& duration)
{
	this->duration = duration;
}

void Score::setMoves(const unsigned int& moves)
{
	this->moves = moves;
}

void Score::set(const unsigned int& points, const unsigned int& length, const unsigned int& moves, const int& duration)
{
	this->points = points;
	this->length = length;
	this->moves = moves;
	this->duration = duration;
}

// Operator overloading defintions

std::ostream& operator<<(std::ostream& out, const Score& score)
{
	out << "\n\n\t" << score.points << "\t\t\t" << score.length << "\t\t\t"
		<< score.duration;
	return out;
}

std::ifstream& operator>>(std::ifstream& fin, Score& score)
{
	fin >> score.id >> score.points >> score.length >> score.duration >> score.moves;

	return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const Score& score)
{
	fout << "\n\n" << score.id << '\n' << score.points
		<< "\t\t" << score.length << "\t\t" << score.duration << "\t\t" << score.moves;
	fout.flush();
	return fout;
}

Score& Score::operator+=(const Score& rhs)
{
	points += rhs.points;
	length += rhs.length;
	duration += rhs.duration;
	moves += rhs.moves;
	return *this;
}

Score& Score::operator/=(const unsigned int& num)
{
	points /= num;
	length /= num;
	duration /= num;
	moves /= num;
	return *this;
}