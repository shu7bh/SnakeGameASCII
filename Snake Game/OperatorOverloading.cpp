#include <fstream>

#include "GlobalAndConstants.h"

std::ifstream& operator>>(std::ifstream& fin, Player& player)
{		// Overloading operator >> to get the input of Player class form the file

	fin >> player.username >> player.password;

	player.score.clear();	// So that the previous scores stored in scores will
	unsigned int points, length, moves;	// clear out since this is a reference variable
	int duration;
	while (fin >> points >> length >> duration >> moves)	// 1 is the termination points
		if (points == 1)	// So we dont need to store that
			break;
		else
			player.score.push_back({ points, length, moves, duration });	// pushing back points in scores

	return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const Player& player)
{	// overloading for the << operator for file stream
	fout << player.username << '\n' << player.password;

	for (const Score& score : player.score)	// The auto will take the data type of Score struct
		fout << '\n' << score.getPoints() << "\t\t" << score.getLength()
		<< "\t\t" << score.getDuration() << "\t\t" << score.getMoves();

	fout << '\n' << 1 << "\t\t" << 1 << "\t\t" << 1 << "\t\t" << 1; // Will help us to know where 
	return fout; // the end of the particular score is
}

std::ostream& operator<<(std::ostream& out, const std::vector<std::string>& data)
{
	for (auto element : data)	// Iterating through the vector
		std::cout << '\t' << element << std::endl;
	return out;
}


std::ostream& operator<<(std::ostream& out, const std::vector<Score>& score)
{
	for (unsigned int i = 0; i < 5 && i < score.size(); i++)
		std::cout << score[i];

	return out;
}