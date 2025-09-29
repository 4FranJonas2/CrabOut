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
		bool powerActive;
		bool gameEnd;
	};

	void PowersCleaner(Player& player);
	void InitPlayer(Player& player, SceneStatus initGame);
	void UpdatePlayer(Player& player);
	void CheckPlayerWinStatus(Player player, SceneStatus& gameStatus);
	void CheckPlayerColisionArena(Player& player, int screenHeight);
	bool IsPlayerAlive(Player player);
	bool HasPlayerReachMaxPoints(Player player);
	void DrawPlayer(Player player);
}

