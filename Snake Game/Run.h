#pragma once
#include "Score.h"
#include "Record.h"

// Function Declarations

//void addNewFood();

void firstTime(const unsigned int& val);

void input();

bool game();

void pauseGame();

void sort();

void sort(std::vector<Record>& score);

void getPlayerRecords(std::vector<Record>& score);

void getGuestRecords(std::vector<Record>& score);

void startingGame();