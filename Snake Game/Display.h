#pragma once

#include "GlobalAndConstants.h"

#include <fstream>

namespace Display
{
	void Field();

	void File(std::string fileName);

	unsigned int Menu();

	void HighScores();

	void pScore();

	void gScore();
}

std::ostream& operator<<(std::ostream&, const std::vector<Score>&);

std::ostream& operator<<(std::ostream&, const std::vector<std::string>&);