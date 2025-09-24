#include "ball.h"

#include <iostream>

#include <ctime>
#include <math.h>

namespace crabOut
{
	BallDir ballDir;

	void InitBall(Ball& ball, int screenWidth, int screenHeight)
	{
		float initBallPosX = screenWidth;
		float initBallPosY = screenHeight;

		Vector2 ballPosition = { screenWidth / 2.0f, screenHeight / 2.0f };
		Vector2 ballSped = {350.0f, 350.0f };

		//ball.ballSize = 
		ball.ballColor.r = 255;
		ball.ballColor.g = 153;
		ball.ballColor.b = 51;
		ball.ballSpeed = ballSped;
		ball.ballCircle.pos.x = ballPosition.x;
		ball.ballCircle.pos.y = ballPosition.y;
		ball.ballCircle.rad = 15.0f;
		ball.frameCounter = 0;
	}

	void UpdateBall(Ball& ball)
	{	
			ball.ballCircle.pos.x += ball.ballSpeed.x * slGetDeltaTime();
			ball.ballCircle.pos.y += ball.ballSpeed.y * slGetDeltaTime();
	}

	bool CheckCollisionBallPlayer(Ball& ball, Rectangle playerRec)
	{
		if (ball.ballCircle.pos.x + ball.ballCircle.rad >= playerRec.recPos.x &&  //izquierda
			ball.ballCircle.pos.x - ball.ballCircle.rad <= playerRec.recPos.x + playerRec.recSize.x && //derecha
			ball.ballCircle.pos.y + ball.ballCircle.rad >= playerRec.recPos.y && //arriba
			ball.ballCircle.pos.y - ball.ballCircle.rad <= playerRec.recPos.y + playerRec.recSize.y) //abajo
		{
			//golpe por derecha
			if (ball.ballCircle.pos.x - ball.ballCircle.rad > playerRec.recPos.x + playerRec.recSize.x)
			{
				ball.ballCircle.pos.x = playerRec.recPos.x + ball.ballCircle.rad + playerRec.recSize.x;
			}

			//golpe por izquierda
			if (ball.ballCircle.pos.x + ball.ballCircle.rad < playerRec.recPos.x)
			{
				ball.ballCircle.pos.x = playerRec.recPos.x - ball.ballCircle.rad;
			}

			//golpe por arriba
			if (ball.ballCircle.pos.y - ball.ballCircle.rad < playerRec.recPos.y)
			{
				ball.ballCircle.pos.y = playerRec.recPos.y - ball.ballCircle.rad;
			}

			//golpe por abajo
			if (ball.ballCircle.pos.y + ball.ballCircle.rad > playerRec.recPos.y + playerRec.recSize.y)
			{
				ball.ballCircle.pos.y = playerRec.recPos.y + playerRec.recSize.y + ball.ballCircle.rad;
			}

			ball.ballSpeed.x *= -1.0f;
			ball.ballSpeed.y *= -1.0f;

			return true;
		}

		else
		{
			return false;
		}
	}

	void CheckCollisionBallArena(Ball& ball, int& player1Points, SceneStatus& resetPoint, int screenWidth, int screenHeight)
	{
		int winScore = 3;
		//chequeo de rebote con los bordes de la arena
		//rebote derecho e izquierdo bas abajo
		if (ball.ballCircle.pos.x >= (screenWidth - ball.ballCircle.rad))
		{
			ball.ballCircle.pos.x = screenWidth - ball.ballCircle.rad;
			ball.ballSpeed.x *= -1.0f;
			player1Points++;
			if (player1Points < winScore)
			{
				resetPoint = SceneStatus::RESETGAME;
			}
		}

		//rebote inferior y superior
		if (ball.ballCircle.pos.y >= (screenHeight - ball.ballCircle.rad))
		{
			ball.ballCircle.pos.y = (screenHeight - ball.ballCircle.rad);
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
		slCircleFill(ball.ballCircle.pos.x, ball.ballCircle.pos.y,
			ball.ballCircle.rad,50);
	}
}