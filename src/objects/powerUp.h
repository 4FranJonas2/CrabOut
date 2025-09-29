#pragma once

#include "sl.h"

#include "../utilities.h"

namespace crabOut
{
	struct PowerUp
	{
		Circle powerCircle;
		Colors powerColor;
		int powerSpeed;
		bool brickHit;
		bool isActive = false;
		bool isRedPower;
		bool isYellowPower;
		bool isGreenPower;
	};

	void CreatePowerUp(PowerUp powers[], Vector2& brickPos, bool& brickHit);
	void UpdatePowerUp(PowerUp powers[], Rectangle& playerRec, float& playerSpeed, bool& modActive);
	bool CheckCollisionPowerPlayer(PowerUp powers[], Rectangle playerRec);
	void CheckCollisionBallArena(PowerUp powers[]);
	void DrawPowerUp(PowerUp powers[]);
	void ResetPowerUps(PowerUp powers[], GameStats gamestats, Vector2& brickPos, bool& brickHit);
}