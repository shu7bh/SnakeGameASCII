
#include <Windows.h>
#include <fstream>

#include "GlobalAndConstants.h"

void mainMenu()	// The menu that will be displayed when the program runs
{
	CHOICE choice = static_cast<CHOICE> (Display::Menu());	// getting the choice of the user

	Player player;
	int a;	// not needed, just taking the value from _getch(), No need whatsoever

	switch (choice)
	{
	case CHOICE::LOGIN:	// The person has opted to logIn

		while (!logIn());

		Display::File("YourRecord.txt");

		for (unsigned int i = 0; i < GAME::player.score.size(); i++)
			std::cout << GAME::player.score[i];// Her/His precceding scores will be displayed

		a = _getch();	// So that the program waits for the user

		break;

	case CHOICE::SIGNUP:
		while (!signUp());	// The program will create a new Player

		break;

	case CHOICE::GUEST:
		newGuest();	// A new Guest ID will be made
	default:
		break;
	}
	system("CLS");
}

bool logIn()
{
	bool isLoggedIn = false;
	std::string str, ask;

	Display::File("Login.txt");

	ask = "\n\t\t\tENTER USERNAME: ";

	std::string username, password;

	std::cin.ignore();
	std::cout << ask;

	std::getline(std::cin, username);


	toUppercase(username);

	std::ifstream idFile("PlayerRecords.txt", std::ios::in | std::ios::out);

	Player player;

	while (idFile >> player)	// using operator overloading to read the class Player
		if (player.getUsername() == username)	// if the usernames r same, it will
		{					// have to match the passwords 
			unsigned int tries = 5; // Gives a max of 5 tries to ge the correct password
			do
			{
				std::cout << "\n\t\t\tENTER YOUR PASSWORD: ";
				std::getline(std::cin, password);

				toUppercase(password);

				if (player.getPassword() == password)
				{
					std::cout << "\n\t\t\tSUCCESSFULLY LOGGED IN\n";
					GAME::player = player;	//Password matches and user is 
					return true; // successfully logged in
				}
			} while (tries--);

			std::cerr << "\n\t\tUSERNAME AND PASSWORD IS NOT MATCHING\n\n\t\t\tEXITING THE GAME";
			Display::File("End.txt");
			exit(-1);	// Even after 5 tries the passwords arent matching
		}
	std::cout << "\n\t\t\tWRONG USERNAME\n\n\t\t\tENTER AGAIN\n\n";
	Sleep(1000);	// To show the above message to the user

	std::cout << "\n\t\t\tDO YOU WANT TO EXIT GAME (Y/N): ";
	char ch;
	ch = std::toupper(std::cin.get());	// Whether the user wants to exit game due to 
	if (ch == 'Y')
	{
		Display::File("End.txt");
		// selection of wrong choice
		exit(-1);
	}
	return false;
}

void toUppercase(std::string& str)
{
	for (char& ch : str)
		ch = std::toupper(ch);
}

bool signUp()
{
	bool isSignedIn = true;

	system("CLS");

	std::string ask;

	Display::File("SignUp.txt");

	ask = "\n\t\t\tENTER USERNAME: ";

	std::string username, password;

	static unsigned int ct = 0;

	if (!ct++)
		std::cin.ignore();	// Since the 1st char was being ignored for other cases

	bool badUsername = true;
	do
	{
		std::cout << ask;
		std::getline(std::cin, username);

		try
		{
			if (username.size() == 0)
				throw "CANT'T HAVE USERNAMES WITH NO CHARACTERS";

			if (std::count(username.begin(), username.end(), ' '))
				throw "CAN'T HAVE USERENAMES WITH SPACES";

			if (std::isdigit(username[0]))
				throw "CAN'T HAVE USERNAMES STARTING WITH NUMBERS";

			badUsername = false;
		}
		catch (const char* error)
		{
			std::cout << "\n\n\t\t" << error << " TRY AGAIN\n";
		}

	} while (badUsername);

	toUppercase(username);

	std::ifstream idFile;

	idFile.open("PlayerRecords.txt", std::ios::in | std::ios::out);

	Player player;

	isSignedIn = true;

	while (idFile >> player)	// Using operator overloading to input data
		if (player.getUsername() == username)
		{
			std::cout << "\n\n\t\t\tUSERNAME ALREADY EXISTS";
			int a = _getch();	// we are using _getch() to just allow the user to
			isSignedIn = false;	// show the next phase
			break;
		}

	idFile.close();

	if (isSignedIn)	// If the user successfully signed in
	{
		std::cout << "\n\n\t\t\tENTER PASSWORD: ";
		std::getline(std::cin, password);

		toUppercase(password);

		GAME::player = Player(username, password);
	}
	return isSignedIn;
}

void newGuest()
{
	std::ifstream fin("GuestRecords.txt");

	while (fin >> GAME::guest);

	GAME::guest.setId(GAME::guest.getId() + 1);

	fin.close();
}
