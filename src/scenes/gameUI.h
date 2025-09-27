#pragma once

#include "sl.h"

#include "..\utilities.h"

#include <string>

namespace crabOut
{
	void PrintScore(int playerScore, GameStats gameStats);
	void PrintLives(int playerLives, GameStats gameStats);

	//void PrintEndMatchMsg(int player1Score, int player2Score, SceneStatus& gameScene);
	//void PrintRules();
	//void PrintCredits();
	void PrintText(float posX, float posY, std::string text);
}