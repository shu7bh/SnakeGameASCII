#include <Windows.h>
#include <fstream>	// To get input from a file
#include <numeric>

#include "GlobalAndConstants.h"

// CAN ADD DEBRIS OR POISON WHICH CAN EITHER END
// OR REDUCE THE POINTS OF THE PLAYER MEANWHILE SOME COULD INCREASE ITS SPEED
// ADDING HELPER STUFF WHICH REDUCES THE SPEED, INCREASES THE POINTS, REDUCES THE SNAKE
// LENGTH
//

// DECREASE SIZE OF SNAKE FROM THE END

void hideCursor();

bool setField();

void updateRecord();

void initializeAll(unsigned int&);

bool restartGame();

void getLevel();

void initialWork(unsigned int &);

int main()
{
	hideCursor();

	GAME::guest.setId(0);

	unsigned int ct = 0;

	mainMenu();

	if (GAME::guest.getId() != 0)
		ct = 1;
	else
		ct = 0;

	do
	{
		std::thread thread(initialWork, std::ref(ct));

		//if (!setField())	// The file did not open successfully for input
		//	return -1;
		//getLevel();

		getLevel();

		startingGame();

		thread.join();

		Timer time;
		while (game())
			GAME::moves++;

		GAME::duration += time;

		updateRecord();

	} while (restartGame());

	Display::HighScores();

	Display::File("End.txt");

	char t = _getch();

	system("CLS");

	return 0;
}

void hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

#include <random>
#include <time.h>

bool setField()
{
	std::ifstream fin("Field.txt");	// Opening Field.txt
	std::string str;

	if (!fin)	// If the file is unable to open
	{
		std::cerr << "\n\n\t\tUNABLE TO OPEN FILE FOR INPUT\n\n\t\tEXITING THE GAME";
		return false;
	}

	std::getline(fin, str); // Used to ignore the first 
							// line due to some unwanted print

	while (std::getline(fin, str))	// To input the file till its end
		GAME::Field.push_back(str);	// Initializing the Field <vector <string> >

	fin.close();	// Close the file

	std::default_random_engine R(static_cast<unsigned int>(time(0)));

	std::uniform_int_distribution<int> range(0, 4);

	firstTime(range(R));

	return true;
}

void updateRecord()
{
	system("CLS");

	if (GAME::player.getUsername() == "")
	{
		std::cout << "\n\n\n\n\t\t\tGUEST ID: " << GAME::guest.getId();
		std::cout << "\n\n\n\t\t\tFINAL POINTS: " << GAME::points;
		std::cout << "\n\n\n\t\t\tLENGTH: " << GAME::snake.size();
		std::cout << "\n\n\n\t\t\tTIME: " << GAME::duration;
		std::cout << "\n\n\n\t\t\tMOVES TAKEN: " << GAME::moves;
		
		char t = _getch();
		t = _getch();

		GAME::guest.set(GAME::points, GAME::snake.size(), GAME::moves , GAME::duration);

		std::ofstream fout("GuestRecords.txt", std::ios::app);
		fout << GAME::guest;
		return;
	}


	GAME::player.score.push_back({ GAME::points, GAME::snake.size(), GAME::moves, GAME::duration });

	std::cout << "\n\n\t\t\t\tUSERNAME: " << GAME::player.getUsername();
	std::cout << "\n\n\n\tFINAL POINTS: " << GAME::points;
	std::cout << "\t\t\t\tLENGTH: " << GAME::snake.size();
	std::cout << "\n\n\n\tTIME: " << GAME::duration;
	std::cout << "\t\t\t\t\tMOVES TAKEN: " << GAME::moves;

	Score sum(0, 0, 0, 0);

	for (Score& score : GAME::player.score)
		sum += score;

	std::cout << "\n\n\n\n\t\t\t\tTOTAL\n\n\n\tPOINTS: " << sum.getPoints()
		<< "\t\t\t\tLENGTH: " << sum.getLength()
		<< "\n\n\n\tDURATION: " << sum.getDuration()
		<< "\t\t\t\tMOVES TAKEN: " << sum.getMoves();

	sum /= GAME::player.score.size();

	std::cout << "\n\n\n\n\t\t\t\tAVERAGE\n\n\n\tPOINTS: " << sum.getPoints()
		<< "\t\t\t\tLENGTH: " << sum.getLength()
		<< "\n\n\n\tDURATION: " << sum.getDuration()
		<< "\t\t\t\tMOVES TAKEN: " << sum.getMoves();

	char t = _getch();
	t = _getch();
	
	std::ifstream fin("PlayerRecords.txt");
	std::ofstream fout("temp.txt");
	Player player;

	while (fin >> player)
		if (player.getUsername() != GAME::player.getUsername())
			fout << player << "\n\n";

	fout << GAME::player;
	fin.close();
	fout.close();

	try
	{
		if (remove("PlayerRecords.txt"))
			throw "UNABLE TO DELETE FILE";
		if (rename("temp.txt", "PlayerRecords.txt"))
			throw "UNABLE TO RENAME FILE";
	}
	catch (std::string error)
	{
		std::cout << "\n\n\t\t\t" << error << "\n\n\t\t\tDUE TO SAFETY REASONS"
			<< "PROGRAM TERMINATING.\n\n\t\t\t SORRY FOR ANY INCOVENIENCE";
	}
}

void initializeAll(unsigned int& ct)
{
	GAME::Field.clear();
	GAME::snake.clear();
	GAME::points = 0;
	GAME::speed = 70.0f;
	GAME::moves = 0;
	GAME::duration = 0;

	if (ct > 1)
		GAME::guest.setId(GAME::guest.getId() + 1);

	if (ct > 0)
		ct++;

	FOOD::normal.initialize(5.0f);

	FOOD::booster.initialize(0.0f);
}

bool restartGame()
{
	system("CLS");

	std::cout << "\n\n\t\t\tDO YOU WANT TO PLAY AGAIN (Y/N): ";
	char choice;

	std::cin >> choice;

	choice = std::toupper(choice);

	return choice == 'Y';
}

void getLevel()
{
	bool notDone = true;

	unsigned int level;

	do
	{
		Display::File("Level.txt");

		std::cout << "\n\n\t\t\tLEVEL: ";

		try
		{
			std::cin >> level;
			if (!std::cin)
				throw "WRONG INPUT";
			if (level < 1 || level > 5)
				throw "ENTER BETWEEN 1 AND 5 ONLY";

			notDone = false;
		}
		catch (const std::string error)
		{
			std::cout << "\n\n\t\t" << error << ". ENTER AGAIN";
		}

	} while (notDone);

	switch (level)
	{
	case 1:
		GAME::speed = 400.0f;
		break;

	case 2:
		GAME::speed = 130.0f;
		break;

	case 3:
		GAME::speed = 80.0f;
		break;

	case 4:
		GAME::speed = 55.0f;
		break;

	case 5:
		GAME::speed = 35.0f;
		break;

	default:
		break;
	}
}

void initialWork(unsigned int& ct)
{
	initializeAll(ct);

	if (!setField())
		return;
}