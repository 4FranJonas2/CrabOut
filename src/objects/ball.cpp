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
		float initBallPosY = 35.0;
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

	void CheckCollisionBallArena(Ball& ball, int& player1Points, SceneStatus& resetPoint, Pong gameStats)
	{
		int winScore = 3;
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