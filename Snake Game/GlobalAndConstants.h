#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <thread>

#include "Snake.h"
#include "Menu.h"
#include "Player.h"
#include "Display.h"
#include "Run.h"
#include "Record.h"
#include "Timer.h"
#include "Types.h"

// All the global variables and constants will be declared 
//	in this file for use throughout the game
typedef const char cc;

namespace GAME
{
	extern std::vector <std::string> Field;
	// The main area where the snake will be moving around in the game

	extern std::vector <Snake> snake;

	cc FREE = ' ';

	cc PAUSE = 'p';

	extern unsigned int points;

	extern Player player;

	extern Score guest;

	extern int duration;

	extern float speed;

	extern unsigned int moves;
}

namespace MOVE
{
	cc UP = 'w';
	cc DOWN = 's';
	cc LEFT = 'a';
	cc RIGHT = 'd';
}
#include <map>

namespace FOOD
{
	extern Types normal, booster;
}

enum class CHOICE
{
	LOGIN = 1, SIGNUP, GUEST
};