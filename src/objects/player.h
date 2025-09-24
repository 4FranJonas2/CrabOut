#pragma once

#include "sl.h"

#include "../utilities.h"

namespace crabOut
{
	

	struct Player
	{
		Rectangle playerRec;

		Colors playerColor;
		int playerPoints;
		int playerLives;
		float playerVel;
		bool gameEnd;
	};

	void InitPlayer(Player& player, SceneStatus initGame);
	void UpdatePlayer(Player& player);
	void CheckPlayerPoints(int playerpoints, SceneStatus& gameStatus);
	void CheckPlayerColisionArena(Player& player, int screenHeight);
	void DrawPlayer(Player player);
}

