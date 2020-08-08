#include "GlobalAndConstants.h"

Timer::Timer()
{
	//start = std::chrono::high_resolution_clock::now();

	start = std::chrono::high_resolution_clock::now();
}

bool Timer::operator<=(const int& time)
{
	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	
	if (duration.count() <= time)
		return true;
	return false;
}

int& operator+=(int& dur, const Timer& time)
{
	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - time.start);

	dur += static_cast<int>(duration.count());

	return GAME::duration;
}

int& operator-=(int& dur, const Timer& time)
{
	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - time.start);

	dur -= static_cast<int>(duration.count());

	return dur;
}