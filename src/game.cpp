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

			// background glow
			slSetForeColor(0.1, 0.9, 0.2, 0.4);

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
			slWindow(400, 400, "CrabOut", false);
			InitPlayer(player1, player1.initPlayer1PosX,gameStats.gameManager);
			InitPlayer(player2, player2.initPlayer2PosX, gameStats.gameManager);
			InitBall(ball, gameStats.screenWidth, gameStats.screenHeight);
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
		case SceneStatus::GAMEPLAYTWOPLAYERS:

			bool ballIsHitP1;
			bool ballIsHitP2;

			if (slGetKey(SL_KEY_ENTER) && gameStats.gameManager == SceneStatus::GAMEPLAYTWOPLAYERS)
			{
				gameStats.gameManager = SceneStatus::GAMEPAUSE;
			}

			if (gameStats.gameManager == SceneStatus::GAMEPLAYTWOPLAYERS)
			{
				UpdatePlayer(player1, slGetKey('a'), slGetKey('d'));
				CheckPlayerColisionArena(player1, gameStats.screenHeight);
				CheckCollisionBallArena(ball, player1.playerPoints, gameStats.gameManager, gameStats.screenWidth, gameStats.screenHeight);
				ballIsHitP1 = CheckCollisionBallPlayer(ball, player1.playerRec);
				CheckPlayerPoints(player1.playerPoints, gameStats.gameManager);
				UpdateBall(ball);
			}
			break;

		case SceneStatus::GAMEPAUSE:

			if (slGetKey('p')|| slGetKey('P') && gameStats.gameManager == SceneStatus::GAMEPAUSE)
			{
				gameStats.gameManager = SceneStatus::GAMEPLAYTWOPLAYERS;
			}
			break;

		case SceneStatus::RESETGAME:

			InitPlayer(player1, player1.initPlayer1PosX, gameStats.gameManager);
			InitBall(ball, gameStats.screenWidth, gameStats.screenHeight);
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
		int auxPosXPlayer2 = 570;

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
	
		case SceneStatus::GAMEPLAYTWOPLAYERS:

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