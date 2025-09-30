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
		float frames = 3;
		float frameWidth = 1.0f / frames;
		double startTime = slGetTime();
		int currentFrame = 0;
	};

	void PowersCleaner(Player& player, float powerCoolDown, float lastPowerTime);
	void InitPlayer(Player& player, SceneStatus initGame);
	void UpdatePlayer(Player& player);
	void CheckPlayerWinStatus(Player player, SceneStatus& gameStatus);
	void CheckPlayerColisionArena(Player& player, int screenHeight);
	bool IsPlayerAlive(Player player);
	bool HasPlayerReachMaxPoints(Player player);
	void DrawPlayer(Player& player, GameStats& gamePlayer);
}