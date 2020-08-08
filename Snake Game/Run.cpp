#include <Windows.h>	// For clearing the screen
#include <fstream>
#include <random>
#include <time.h>

#include "GlobalAndConstants.h"

bool game()
{
	//addNewFood();

	FOOD::normal.addFood();

	FOOD::booster.addFood();
	
	Display::Field();

	std::thread thread(input);

	for (unsigned int i = 0; i < GAME::snake.size() - 1; i++)
		GAME::snake[i + 1].setNextDir(GAME::snake[i].getDir());
	// Setting the next direction of the parts as the current direction of the
	// part it is following of

	bool flag = false, addAtEnd = true;

	//To check whether the snake part hit the normalFood or not
#define TAIL(p) GAME::snake.back().p()

	Snake temp(TAIL(getDir), TAIL(getX), TAIL(getY));
	// Creating a temporary snake part which may go to the 
				// end of the snake if the snake eats normalFood
#undef TAIL
	thread.join();

	for (unsigned int i = 0; i < GAME::snake.size(); i++)
		if (!GAME::snake[i].move(flag, addAtEnd))
			// If the snake part has encountered something
			if (!flag)
				return false; // if the snake has not encountered normalFood

	if (flag && addAtEnd)	// if the snake had encountered normalFood
		GAME::snake.push_back(temp);	// adding another part to the snake

	system("CLS");

	return true;
}

std::default_random_engine R(static_cast<unsigned int>(time(0)));	// To generate random numbers

void firstTime(const unsigned int& val)
{
	char dir;

	switch (val)
	{
	case 0:	dir = MOVE::UP; break;
	case 1:	dir = MOVE::DOWN; break;
	case 2: dir = MOVE::LEFT; break;
	case 3: dir = MOVE::RIGHT; break;

	default: dir = MOVE::RIGHT; break;
	}

	std::uniform_int_distribution <unsigned int> r
	(GAME::Field.size() / 2 - 3, GAME::Field.size() / 2 + 3);

	std::uniform_int_distribution <unsigned int> c
	(GAME::Field.begin()->size() / 2 - 3, GAME::Field.begin()->size() / 2 + 3);

	GAME::snake.push_back(Snake(dir, r(R), c(R)));
}

void input()
{
	unsigned int timer = 0;

	Sleep(static_cast<DWORD> (GAME::speed));	// So as to slow down the game and provide enough time for the user
	GAME::speed -= 0.005f;			// to enter a new direction
			// Speed decrease making the game faster progressively
	if (!_kbhit())	// if the user did not press any key
		return;

	char move = std::tolower(_getch());

#define Comp(x, y) \
	move == MOVE::x && GAME::snake.begin()->getDir() == MOVE::y || \
	move == MOVE::y && GAME::snake.begin()->getDir() == MOVE::x

	if (GAME::snake.size() > 1)	// To check whether the snake has a size greater than 1
		if (Comp(UP, DOWN) || Comp(LEFT, RIGHT))	// As then it cant move 2 oppoite 
			return;		// directions at the successive times

	switch (move)
	{
	case MOVE::UP:
	case MOVE::DOWN:			// Setting the direction of the head
	case MOVE::LEFT:			// to the direction provided by the player
	case MOVE::RIGHT:

		GAME::snake.begin()->setNextDir(move);
		break;

	case GAME::PAUSE:

		pauseGame();
		break;

	default:
		break;
	}

#undef Comp
}

void pauseGame()
{
	Timer time;
	
	do
	{
		Display::File("Pause.txt");

		int choice;

		std::cout << "\n\n\n\t\t\tENTER YOUR CHOICE: ";

		try
		{
			std::cin >> choice;
			if (!std::cin)
				throw "PLEASE ENTER A NUMBER FROM THE CHOICES GIVEN ABOVE.";
		}
		catch (const char* error)
		{
			std::cout << "\n\n\n\t\t\t" << error << " ENTER AGAIN";
			continue;
		}
		char t;

		switch (choice)
		{
		case 1:

			GAME::duration -= time;

			startingGame();

			return;

		case 2:

			system("CLS");

			if (GAME::guest.getId() == 0)
				std::cout << "\n\n\n\n\t\t\tUSERNAME: " << GAME::player.getUsername();
			else
				std::cout << "\n\n\n\n\t\t\tGUEST ID: " << GAME::guest.getId();

			std::cout << "\n\n\n\t\t\tPOINTS: " << GAME::points 
				<< "\n\n\n\t\t\tLENGTH: " << GAME::snake.size() 
				<< "\n\n\n\t\t\tMOVES: " << GAME::moves;

			t = _getch();

			break;

		default:
			break;
		}

	} while (time <= 300);

	GAME::duration -= time;

	startingGame();
}


void sort()
{
	std::sort(GAME::player.score.begin(), GAME::player.score.end(),
		[](const Score& a, const Score& b)
		{
			if (a.getPoints() > b.getPoints())
				return true;

			if (a.getPoints() < b.getPoints())
				return false;

			if (a.getDuration() < b.getDuration())
				return true;

			if (a.getDuration() > b.getDuration())
				return false;

			if (a.getMoves() < b.getMoves())
				return true;

			if (a.getMoves() > b.getMoves())
				return false;

			return a.getLength() <= b.getLength();
		});
}

void sort(std::vector<Record>& score)
{
	std::sort(score.begin(), score.end(),
		[](const Record& a, const Record& b)
		{
			if (a.getPoints() > b.getPoints())
				return true;

			if (a.getPoints() < b.getPoints())
				return false;

			if (a.getDuration() < b.getDuration())
				return true;

			if (a.getDuration() > b.getDuration())
				return false;

			if (a.getMoves() < b.getMoves())
				return true;

			if (a.getMoves() > b.getMoves())
				return false;

			if (a.getLength() < b.getLength())
				return true;

			if (a.getLength() > b.getLength())
				return false;

			if (a.getId() && b.getName() != "")	// getId() return 0 if the user is
				return false;		// not a guest

			if (a.getName() != "" && b.getId())
				return true;

			if (a.getId() && b.getId())
				return a.getId() < b.getId();

			return a.getName() < b.getName();
		});
}

void getPlayerRecords(std::vector<Record>& records)
{
	Player player;
	std::ifstream playerIn("PlayerRecords.txt");

	while (playerIn >> player)
		for (Score& score : player.score)
			records.push_back({ player.getUsername(), score });
}

void getGuestRecords(std::vector<Record>& score)
{
	Score guest;
	std::ifstream guestIn("GuestRecords.txt");

	while (guestIn >> guest)
		score.push_back({ guest.getId(),Score(guest.getPoints(), guest.getLength(), guest.getMoves(), guest.getDuration()) });
}

void startingGame()
{
	Display::File("Rules.txt");
	char t = _getch();

	for (unsigned int i = 3; i; i--)
	{
		Display::File("GameIsStarting.txt");

		std::cout << "\n\n\n\n\t\t\t\t     " << i;

		Sleep(1000);
	}
}
