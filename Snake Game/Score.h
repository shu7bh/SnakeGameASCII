#pragma once
#include <iostream>

class Score
{
protected:

	unsigned int id, points, length, moves;

	int duration;

public:

	Score() = default;

	Score(const Score&);

	Score(const unsigned int&, const unsigned int&,
		const unsigned int&, const unsigned int&, const int&);

	Score(const unsigned int&, const unsigned int&,
		const unsigned int&, const int&);

public:

	unsigned int getId() const;

	unsigned int getPoints() const;

	unsigned int getLength() const;

	int getDuration() const;

	unsigned int getMoves() const;
	   
public:

	void setId(const unsigned int&);

	void setPoints(const unsigned int&);

	void setLength(const unsigned int&);

	void setDuration(const int&);

	void setMoves(const unsigned int&);
	
	void set(const unsigned int&, const unsigned int&, const unsigned int&,
		const int&);

public:

	friend std::ostream& operator<<(std::ostream&, const Score&);

	friend std::ifstream& operator>>(std::ifstream&, Score&);

	friend std::ofstream& operator<<(std::ofstream&, const Score&);

	Score& operator+=(const Score&);

	Score& operator/=(const unsigned int&);
};
