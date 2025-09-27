#pragma once

#include "sl.h"

#include "..\utilities.h"

#include <string>

namespace crabOut
{
	void gamePlayUi(int playerLives, int playerScore, GameStats gameStats);
	void PrintText(float posX, float posY, std::string text);
}