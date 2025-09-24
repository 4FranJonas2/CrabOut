#pragma once

#include "sl.h"

#include "../utilities.h"

namespace crabOut
{
	

	struct Player
	{
		float initPlayer1PosX = 10;
		float initPlayer2PosX = 775;

		Rectangle playerRec;

		Colors playerColor;
		int playerPoints;
		int playerLives;
		float playerVel;
		bool gameEnd;
	};

	void InitPlayer(Player& player, float initPlayerPosX, SceneStatus initGame);
	void UpdatePlayer(Player& player, int key1, int key2);
	void CheckPlayerPoints(int playerpoints, SceneStatus& gameStatus);
	void CheckPlayerColisionArena(Player& player, int screenHeight);
	void DrawPlayer(Player player);
}

