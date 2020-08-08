#pragma once
#include <chrono>
#include "GlobalAndConstants.h"

class Timer
{
	//std::chrono::time_point<std::chrono::steady_clock> start;

	std::chrono::time_point<std::chrono::steady_clock> start;
	
public:

	Timer();

	friend int& operator+=(int&, const Timer&);

	friend int& operator-=(int&, const Timer&);

	bool operator<=(const int&);
};