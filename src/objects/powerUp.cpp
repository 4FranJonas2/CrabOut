#include "powerUp.h"

#include <ctime>
#include <cstdlib>

namespace crabOut
{
	void CreatePowerUp (PowerUp& powers, Rectangle brick)
	{
		srand(time(nullptr));

		int randPower = 3;
		int powerChosse = 0;

		powers.powerRad = 8;

		powers.powerPos.x = brick.recPos.x;
		powers.powerPos.y = brick.recPos.y;

		powers.powerSpeed = 100;

		powerChosse = 0 + rand() % randPower + 1;

		if (powerChosse == 1)
		{
			//rojo
			powers.powerColor.r = 1.0;
			powers.powerColor.g = 0.0;
			powers.powerColor.b = 0.0;
			powers.powerColor.a = 1.0;
			powers.isRedPower = true;
		}
		if (powerChosse == 2)
		{
			//amarillo
			powers.powerColor.r = 1.0;
			powers.powerColor.g = 1.0;
			powers.powerColor.b = 0.3;
			powers.powerColor.a = 1.0;
			powers.isYellowPower = true;
		}
		if (powerChosse == 3)
		{
			//verrde
			powers.powerColor.r = 0.0;
			powers.powerColor.g = 1.0;
			powers.powerColor.b = 0.0;
			powers.powerColor.a = 1.0;
			powers.isGreenPower = true;
		}	
	}
	void UpdatePowerUp(PowerUp& powers, Rectangle& playerRec)
	{
		powers.powerPos.y -= powers.powerSpeed * slGetDeltaTime();

		if (CheckCollisionPowerPlayer(powers,playerRec))
		{

		}
	}

	bool CheckCollisionPowerPlayer(PowerUp& powers, Rectangle playerRec)
	{
		float left = playerRec.recPos.x - playerRec.recSize.x / 2;
		float right = playerRec.recPos.x + playerRec.recSize.x / 2;
		float top = playerRec.recPos.y - playerRec.recSize.y / 2;
		float bottom = playerRec.recPos.y + playerRec.recSize.y / 2;

		if (powers.powerPos.x + powers.powerRad >= left)
		{
			return true;
		}
		if (powers.powerPos.x - powers.powerRad <= right )
		{
			return true;
		}
		if (powers.powerPos.y + powers.powerRad >= top )
		{
			return true;
		}
		if (powers.powerPos.y - powers.powerRad <= bottom)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void CheckCollisionBallArena(Ball& ball, int& playerLives, GameStats& gameStats)
	{
		//chequeo de rebote con los bordes de la arena
		//rebote derecho e izquierdo bas abajo
		if (ball.ballCircle.pos.x >= (gameStats.screenWidth - ball.ballCircle.rad))
		{
			ball.ballCircle.pos.x = gameStats.screenWidth - ball.ballCircle.rad;
			ball.ballSpeed.x *= -1.0f;
		}
		else if (ball.ballCircle.pos.x <= (0 + ball.ballCircle.rad))
		{
			ball.ballCircle.pos.x = 0 + ball.ballCircle.rad;
			ball.ballSpeed.x *= -1.0f;
		}

		//rebote superior y inferior
		if (ball.ballCircle.pos.y >= (gameStats.screenHeight - ball.ballCircle.rad))
		{
			ball.ballCircle.pos.y = (gameStats.screenHeight - ball.ballCircle.rad);
			ball.ballSpeed.y *= -1.0f;
		}
		else if (ball.ballCircle.pos.y <= ball.ballCircle.rad)
		{
			ball.ballCircle.pos.y = ball.ballCircle.rad;
			ball.ballSpeed.y *= -1.0f;

			playerLives--;

			gameStats.gameStatus = SceneStatus::RESETGAME;
		}
	}

	void DrawBall(Ball& ball)
	{
		slSetForeColor(ball.ballColor.r, ball.ballColor.g, ball.ballColor.b, 1.0);
		slCircleFill(ball.ballCircle.pos.x, ball.ballCircle.pos.y,
			ball.ballCircle.rad, 50);
	}
}