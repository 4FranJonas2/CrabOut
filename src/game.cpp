#include "game.h"

#include "sl.h"

#include <iostream>

using namespace std;

namespace crabOut
{
	void GamePlay()
	{
		srand(time(nullptr));
		Pong gameStats;
		Player player1;
		Ball ball;

		gameStats.gameManager = SceneStatus::INITGAME;

		Init(player1, ball, gameStats);

		while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
		{
			Update(player1, gameStats, ball);

			Draw(player1, ball, gameStats);
			// draw everything
			slRender();
		}

		// close the window and shut down SIGIL
		slClose();
	}

	void Init(Player& player1, Ball& ball, Pong& gameStats)
	{
		switch ((SceneStatus)gameStats.gameManager)
		{
		case SceneStatus::INITGAME:
			// set up our window and a few resources we need
			slWindow(gameStats.screenWidth, gameStats.screenHeight, "CrabOut", false);
			InitPlayer(player1, gameStats.gameManager);
			InitBall(ball);
			gameStats.gameManager = SceneStatus::GAMEPAUSE;
			break;
		default:
			break;
		}
	}

	void Update(Player& player1, Pong& gameStats, Ball& ball)
	{
		switch ((SceneStatus)gameStats.gameManager)
		{
		case SceneStatus::GAMEPLAY:

			bool ballIsHitP1;

			if (slGetKey(SL_KEY_ENTER) && gameStats.gameManager == SceneStatus::GAMEPLAY)
			{
				gameStats.gameManager = SceneStatus::GAMEPAUSE;
			}

			if (gameStats.gameManager == SceneStatus::GAMEPLAY)
			{
				UpdatePlayer(player1);
				CheckPlayerColisionArena(player1, gameStats.screenWidth);
				CheckCollisionBallArena(ball, player1.playerPoints, gameStats.gameManager, gameStats);
				CheckCollisionBallPlayer(ball, player1.playerRec);
				CheckPlayerPoints(player1.playerPoints, gameStats.gameManager);
				UpdateBall(ball, gameStats, player1.playerRec.recPos.x, player1.playerRec.recPos.y);
			}
			break;

		case SceneStatus::GAMEPAUSE:

			if (slGetKey('P') && gameStats.gameManager == SceneStatus::GAMEPAUSE)
			{
				gameStats.gameManager = SceneStatus::GAMEPLAY;
			}
			break;

		case SceneStatus::RESETGAME:

			InitPlayer(player1, gameStats.gameManager);
			InitBall(ball);
			gameStats.gameManager = SceneStatus::GAMEPAUSE;
			break;

		case SceneStatus::GAMEEND:

			if (slGetKey(SL_KEY_ENTER))
			{
				gameStats.gameManager = SceneStatus::RESETGAME;
				player1.gameEnd = true;
			}
			break;

		default:
			break;
		}
	}

	void Draw(Player player1, Ball& ball, Pong& gameStats)
	{
		int auxPosXPlayer1 = 200;

		switch ((SceneStatus)gameStats.gameManager)
		{
		case SceneStatus::INITGAME:

			//PrintScore(player1.playerPoints, auxPosXPlayer1);
			//PrintArena(gameStats.screenWidth, gameStats.screenHeight);
			DrawPlayer(player1);
			DrawBall(ball);
			//PrintPause();
			//PrintRules();
			//PrintCredits();
			break;

		case SceneStatus::GAMEPLAY:

			//PrintScore(player1.playerPoints, auxPosXPlayer1);
			//PrintArena(gameStats.screenWidth, gameStats.screenHeight);
			DrawPlayer(player1);
			DrawBall(ball);
			break;

		case SceneStatus::GAMEPAUSE:

			//PrintScore(player1.playerPoints, auxPosXPlayer1);
			//PrintArena(gameStats.screenWidth, gameStats.screenHeight);
			DrawPlayer(player1);
			DrawBall(ball);
			//PrintPause();
			//PrintRules();
			//PrintCredits();
			break;

		case SceneStatus::GAMEEND:

			//PrintEndMatchMsg(player1.playerPoints, player2.playerPoints, gameStats.gameManager);
			//PrintScore(player1.playerPoints, auxPosXPlayer1);
			//PrintArena(gameStats.screenWidth, gameStats.screenHeight);
			DrawPlayer(player1);
			DrawBall(ball);
			break;

		default:
			break;
		}
	}
}