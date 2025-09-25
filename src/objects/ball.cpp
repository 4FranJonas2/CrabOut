#include "ball.h"

#include <iostream>

#include <ctime>
#include <math.h>

namespace crabOut
{
	BallDir ballDir;

	void InitBall(Ball& ball)
	{
		ball.ballCircle.rad = 10.0f;
		float initBallPosX = 400.0;
		float initBallPosY = 36.0;
		Vector2 ballPosition = { initBallPosX, initBallPosY };
		Vector2 ballSped = {350.0f, 350.0f };

		//color naranja 
		ball.ballColor.r = 0.9;
		ball.ballColor.g = 0.5;
		ball.ballColor.b = 0.1;

		ball.ballSpeed = ballSped;
		ball.ballCircle.pos.x = ballPosition.x;
		ball.ballCircle.pos.y = ballPosition.y;
		ball.frameCounter = 0;
	}

	void UpdateBall(Ball& ball, Pong gameStatus, int playerPosX, int playerPosY)
	{	
		if (gameStatus.gameManager == SceneStatus::GAMEPAUSE)
		{
			ball.ballCircle.pos.x = playerPosX;
			ball.ballCircle.pos.y = playerPosY;
		}
		else
		{
			ball.ballCircle.pos.x += ball.ballSpeed.x * slGetDeltaTime();
			ball.ballCircle.pos.y += ball.ballSpeed.y * slGetDeltaTime();
		}
	}

	// revote preciso sin polares====
	bool CheckCollisionBallPlayer(Ball& ball, Rectangle playerRec)
	{
		float left = playerRec.recPos.x - playerRec.recSize.x /2;
		float right = playerRec.recPos.x + playerRec.recSize.x /2;
		float top = playerRec.recPos.y - playerRec.recSize.y /2;
		float bottom = playerRec.recPos.y + playerRec.recSize.y /2;

		if (ball.ballCircle.pos.x + ball.ballCircle.rad >= left &&
			ball.ballCircle.pos.x - ball.ballCircle.rad <= right &&
			ball.ballCircle.pos.y + ball.ballCircle.rad >= top &&
			ball.ballCircle.pos.y - ball.ballCircle.rad <= bottom)
		{
			float overlapLeft = fabs((ball.ballCircle.pos.x + ball.ballCircle.rad) - left);
			float overlapRight = fabs(right - (ball.ballCircle.pos.x - ball.ballCircle.rad));
			float overlapTop = fabs((ball.ballCircle.pos.y + ball.ballCircle.rad) - top);
			float overlapBottom = fabs(bottom - (ball.ballCircle.pos.y - ball.ballCircle.rad));

			float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

			if (minOverlap == overlapLeft)
			{
				ball.ballCircle.pos.x = left - ball.ballCircle.rad;
				ball.ballSpeed.x *= -1;
			}
			else if (minOverlap == overlapRight)
			{
				ball.ballCircle.pos.x = right + ball.ballCircle.rad;
				ball.ballSpeed.x *= -1;
			}
			else if (minOverlap == overlapTop)
			{
				ball.ballCircle.pos.y = top - ball.ballCircle.rad;
				ball.ballSpeed.y *= -1;

				float relativeIntersectX = (ball.ballCircle.pos.x - playerRec.recPos.x);
				float normalized = relativeIntersectX / (playerRec.recSize.x /2);

				float speed = sqrt(ball.ballSpeed.x * ball.ballSpeed.x + ball.ballSpeed.y * ball.ballSpeed.y);

				ball.ballSpeed.x = normalized * speed;
				ball.ballSpeed.y = -sqrt(speed * speed - ball.ballSpeed.x * ball.ballSpeed.x);
			}
			else if (minOverlap == overlapBottom) 
			{
				ball.ballCircle.pos.y = bottom + ball.ballCircle.rad;
				ball.ballSpeed.y *= -1;
			}

			return true;
		}

		return false;
	}

	void CheckCollisionBallArena(Ball& ball, int& player1Points, SceneStatus& resetPoint, Pong gameStats)
	{
		//chequeo de rebote con los bordes de la arena
		//rebote derecho e izquierdo bas abajo
		if (ball.ballCircle.pos.x >= (gameStats.screenWidth - ball.ballCircle.rad))
		{
	 		ball.ballCircle.pos.x = gameStats.screenWidth - ball.ballCircle.rad;
			ball.ballSpeed.x *= -1.0f;
			/*player1Points++;
			if (player1Points < winScore)
			{
				resetPoint = SceneStatus::RESETGAME;
			}*/
		}
		else if (ball.ballCircle.pos.x <= (0 + ball.ballCircle.rad))
		{
			ball.ballCircle.pos.x = 0 + ball.ballCircle.rad;
			ball.ballSpeed.x *= -1.0f;
		}

		//rebote inferior y superior
		if (ball.ballCircle.pos.y >= (gameStats.screenHeight - ball.ballCircle.rad))
		{
			ball.ballCircle.pos.y = (gameStats.screenHeight - ball.ballCircle.rad);
			ball.ballSpeed.y *= -1.0f;
		}
		else if (ball.ballCircle.pos.y <= ball.ballCircle.rad)
		{
			ball.ballCircle.pos.y = ball.ballCircle.rad;
			ball.ballSpeed.y *= -1.0f;
		}
	}

	void DrawBall(Ball& ball)
	{
		slSetForeColor(ball.ballColor.r, ball.ballColor.g, ball.ballColor.b, 1.0);
		slCircleFill(ball.ballCircle.pos.x, ball.ballCircle.pos.y,
			ball.ballCircle.rad,50);
	}
}