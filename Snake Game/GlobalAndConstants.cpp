#include "GlobalAndConstants.h"

// initializing GAME::

std::vector <std::string> GAME::Field;

std::vector <Snake> GAME::snake;

unsigned int GAME::points = 0;

Player GAME::player;

Score GAME::guest;

int GAME::duration;

float GAME::speed = 70.0f;

unsigned int GAME::moves = 0;

Types FOOD::normal
(
	{{ 10, 'a' }, { 15, 'r' }, { 20, 'm' }, { 10, 'p' }, { 35, 'l' }, { 25, 's'} },
	5.0f, 0.002f
);

Types FOOD::booster ({ {70, 'B', -2}, {100, 'Z', -1}, {130, 'S', -4} }, 0.0f, 0.002f );