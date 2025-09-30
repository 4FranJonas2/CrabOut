#include "powerUp.h"

#include <ctime>
#include <cstdlib>

namespace crabOut
{
	int maxPowers = 9;
	float lastPowerUpTime = 0.0;
	float powerUpCooldown = 6.0f;

	void CreatePowerUp(PowerUp powers[], Vector2& brickPos, bool& brickHit)
	{
		int maxRand = 3;
		int powerChosse = 0;
		float currentTime = slGetTime();

		if (brickHit && currentTime - lastPowerUpTime >= powerUpCooldown)
		{
			for (int i = 0; i < maxPowers; i++)
			{
				if (powers[i].isActive == false)
				{
					powers[i].powerCircle.rad = 8;

					powers[i].powerCircle.pos.x = brickPos.x;
					powers[i].powerCircle.pos.y = brickPos.y;

					powers[i].powerSpeed = 100;

					powerChosse = 0 + rand() % maxRand + 1;

					if (powerChosse == 1)
					{
						//rojo
						powers[i].powerColor.r = 1.0;
						powers[i].powerColor.g = 0.0;
						powers[i].powerColor.b = 0.0;
						powers[i].powerColor.a = 1.0;
						powers[i].isRedPower = true;
						powers[i].isActive = true;
					}
					if (powerChosse == 2)
					{
						//amarillo
						powers[i].powerColor.r = 1.0;
						powers[i].powerColor.g = 1.0;
						powers[i].powerColor.b = 0.3;
						powers[i].powerColor.a = 1.0;
						powers[i].isYellowPower = true;
						powers[i].isActive = true;
					}
					if (powerChosse == 3)
					{
						//verrde
						powers[i].powerColor.r = 0.0;
						powers[i].powerColor.g = 1.0;
						powers[i].powerColor.b = 0.0;
						powers[i].powerColor.a = 1.0;
						powers[i].isGreenPower = true;
						powers[i].isActive = true;
					}
					powerChosse = 0;
					brickHit = false;
					break;
				}
			}
			lastPowerUpTime = currentTime;
		}

		brickPos.x = 0.0;
		brickPos.y = 0.0;
		brickHit = false;
	}

	void UpdatePowerUp(PowerUp powers[], Rectangle& playerRec, float& playerSpeed, bool& modActive, float& lastPowerTime)
	{
		for (int i = 0; i < maxPowers; i++)
		{
			if (powers[i].isActive == true)
			{
				powers[i].powerCircle.pos.y -= powers[i].powerSpeed * slGetDeltaTime();

				if (CheckCollisionPowerPlayer(powers, playerRec))
				{
					if (powers[i].isGreenPower == true && modActive == false)
					{
						int extraLenght = 200.0;
						playerRec.recSize.x = extraLenght;
						modActive = true;
						lastPowerTime = slGetTime();
					}
					if (powers[i].isYellowPower == true && modActive == false)
					{
						int extraLenght = 40.0;
						playerRec.recSize.x = extraLenght;
						modActive = true;
						lastPowerTime = slGetTime();
					}
					if (powers[i].isRedPower == true && modActive == false)
					{
						int speedDefuf = 200.0;
						playerSpeed = speedDefuf;
						modActive = true;
						lastPowerTime = slGetTime();
					}
					powers[i].isRedPower = false;
					powers[i].isYellowPower = false;
					powers[i].isGreenPower = false;
					powers[i].isActive = false;
				}
				CheckCollisionBallArena(powers);
			}
		}
	}

	bool CheckCollisionPowerPlayer(PowerUp powers[], Rectangle playerRec)
	{
		float left = playerRec.recPos.x - playerRec.recSize.x / 2;
		float right = playerRec.recPos.x + playerRec.recSize.x / 2;
		float top = playerRec.recPos.y - playerRec.recSize.y / 2;
		float bottom = playerRec.recPos.y + playerRec.recSize.y / 2;

		for (int i = 0; i < maxPowers; i++)
		{
			if (powers[i].isActive == true)
			{
				if (powers[i].powerCircle.pos.x + powers[i].powerCircle.rad >= left &&
					powers[i].powerCircle.pos.x - powers[i].powerCircle.rad <= right &&
					powers[i].powerCircle.pos.y + powers[i].powerCircle.rad >= top &&
					powers[i].powerCircle.pos.y - powers[i].powerCircle.rad <= bottom)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}

	void CheckCollisionBallArena(PowerUp powers[])
	{
		//chequeo de rebote con los bordes de la arena
		//rebote derecho e izquierdo bas abajo

		for (int i = 0; i < maxPowers; i++)
		{
			if (powers[i].powerCircle.pos.y < 0 && powers[i].isActive == true)
			{
				powers[i].isRedPower = false;
				powers[i].isYellowPower = false;
				powers[i].isGreenPower = false;
				powers[i].isActive = false;

				break;
			}
		}
	}

	void DrawPowerUp(PowerUp powers[], GameStats gameCoco)
	{
		for (int i = 0; i < maxPowers; i++)
		{
			if (powers[i].isActive == true)
			{
				if (powers[i].isGreenPower == true)
				{
					slSprite(gameCoco.greenCoconut, powers[i].powerCircle.pos.x, powers[i].powerCircle.pos.y, powers[i].powerCircle.rad * 2, powers[i].powerCircle.rad * 2);
				}
				if (powers[i].isYellowPower == true)
				{
					slSprite(gameCoco.yellowCoconut, powers[i].powerCircle.pos.x, powers[i].powerCircle.pos.y, powers[i].powerCircle.rad * 2, powers[i].powerCircle.rad * 2);
				}
				if (powers[i].isRedPower == true)
				{
					slSprite(gameCoco.redCoconut, powers[i].powerCircle.pos.x, powers[i].powerCircle.pos.y, powers[i].powerCircle.rad * 2, powers[i].powerCircle.rad * 2);
				}
			}
		}
	}

	void ResetPowerUps(PowerUp powers[], GameStats gamestats, Vector2& brickPos, bool& brickHit)
	{
		brickPos.x = 0.0;
		brickPos.y = 0.0;
		brickHit = false;

		if (gamestats.gameStatus == SceneStatus::RESETGAME)
		{
			for (int i = 0; i < maxPowers; i++)
			{
				if (powers[i].isActive == true)
				{
					powers[i].isRedPower = false;
					powers[i].isYellowPower = false;
					powers[i].isGreenPower = false;
					powers[i].isActive = false;
				}
			}
		}
	}
}