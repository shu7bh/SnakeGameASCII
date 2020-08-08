#include <Windows.h>
#include <fstream>

#include "GlobalAndConstants.h"

void Display::Field()
{
	std::cout << GAME::Field;

	std::cout << "\n\t\t YOUR POINTS: " << GAME::points
		<< "\t\tSNAKE LENGTH: " << GAME::snake.size();
}

void Display::File(std::string fileName)
{
	std::string str;

	system("CLS");

	try
	{
		std::ifstream fin(fileName);	// Opening Main<enu.txt

		while (std::getline(fin, str))
			std::cout << str << '\n';

		fin.close();
	}
	catch (...)
	{
		std::cerr << "\n\n\t\tUNABLE TO OPEN FILE: " << fileName;
	}
}

unsigned int Display::Menu()
{
	std::string str, ask = "\n\t\t\tWHAT WOULD YOU LIKE TO DO: ";
	unsigned int choice;
	do
	{
		Display::File("MainMenu.txt");

		std::cout << ask;
		try
		{	// To check and prevent a non integer number
			std::cin >> choice;
			if (!std::cin)	// IF the std::cin has taken an input of not a character
				throw "WRONG INPUT. PLEASE ENTER AGAIN";
		}
		catch (std::string error)	// To catch the error
		{
			std::cin.clear();	// Clearing the std::cin(), true and false flag
			std::cin.ignore();	// ignoring what was entered
			std::cout << "\n\n\t\t" << error;
			choice = 0;	// Giving a default value of 0
			Sleep(1000);
		}

	} while (choice < 1 || choice > 3);

	return choice;
}

void Display::HighScores()
{
	if (GAME::player.getUsername() != "")
	{
		Display::pScore();
		char t = _getch();
	}

	Display::gScore();

	char t = _getch();
}

void Display::pScore()
{
	Display::File("PHighScore.txt");

	GAME::player.score;

	sort();

	std::cout << GAME::player.score;
}

void Display::gScore()
{
	Display::File("GHighScore.txt");

	std::vector<Record> allRecords;

	getPlayerRecords(allRecords);

	getGuestRecords(allRecords);

	sort(allRecords);

	for (unsigned int i = 0; i < 5 && i < allRecords.size(); i++)
	{
		std::cout << "\n\n\t";

		if (allRecords[i].getId())
			std::cout << allRecords[i].getId();
		else
			std::cout << allRecords[i].getName();

		std::cout << "\t\t" << allRecords[i].getPoints() << "\t\t"
			<< allRecords[i].getLength() << "\t\t" << allRecords[i].getDuration();
	}
}