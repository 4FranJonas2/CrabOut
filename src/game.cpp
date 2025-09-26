#include "game.h"

#include "sl.h"

#include "objects/player.h"
#include "objects/ball.h"
#include "scenes/gameUI.h"
#include "objects/brick.h"

#include <iostream>

using namespace std;

namespace crabOut
{
	const int maxBricks = 30;
	GameStats gameStats;
	Player player1;
	Ball ball;
	Brick bricks[maxBricks];

	void Init(Player& player1, Ball& ball, GameStats& gameStats, Brick brick[]);
	void Update(Player& player1, GameStats& gameStats, Ball& ball, Brick brick[]);
	void Draw(Player player1, Ball& ball, GameStats& gameStats, Brick brick[]);
	void DeInit(GameStats& gameStats);

	void RunGame()
	{
		srand(time(nullptr));
		gameStats.gameStatus = SceneStatus::INITGAME;

		Init(player1, ball, gameStats, bricks);

		while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
		{
			Update(player1, gameStats, ball, bricks);

			Draw(player1, ball, gameStats, bricks);
			// draw everything
			slRender();
		}

		// close the window and shut down SIGIL
		slClose();
	}

	void Init(Player& player1, Ball& ball, GameStats& gameStats, Brick gameBrick[])
	{
		switch ((SceneStatus)gameStats.gameStatus)
		{
		case SceneStatus::INITGAME:
		{
			// set up our window and a few resources we need
			slWindow(gameStats.screenWidth, gameStats.screenHeight, "CrabOut", false);

			InitPlayer(player1, gameStats.gameStatus);
			InitBrick(gameBrick, maxBricks, gameStats);
			InitBall(ball);

			gameStats.gameStatus = SceneStatus::FIRSTGAME;

			int font = slLoadFont("res/dogicapixel.ttf");
			slSetFont(font, 14);

		}
			break;
		default:
			break;
		}
	}

	void Update(Player& player1, GameStats& gameStats, Ball& ball, Brick gameBrick[])
	{
		switch ((SceneStatus)gameStats.gameStatus)
		{
		case SceneStatus::FIRSTGAME:

			if (slGetKey(SL_KEY_ENTER) && gameStats.gameStatus == SceneStatus::FIRSTGAME)
			{
				gameStats.gameStatus = SceneStatus::GAMEPLAY;
			}

			if (gameStats.gameStatus == SceneStatus::FIRSTGAME)
			{
				CheckPlayerColisionArena(player1, gameStats.screenWidth);
				//CheckCollisionBallPlayer(ball, player1.playerRec);
				UpdatePlayer(player1);
				UpdateBall(ball, gameStats, player1.playerRec.recPos.x, player1.playerRec.recPos.y);
			}
			break;

		case SceneStatus::GAMEPLAY:

			bool ballIsHitP1;

			if (slGetKey(SL_KEY_ENTER) && gameStats.gameStatus == SceneStatus::GAMEPLAY)
			{
				gameStats.gameStatus = SceneStatus::GAMEPAUSE;
			}


			if (gameStats.gameStatus == SceneStatus::GAMEPLAY)
			{
				CheckPlayerColisionArena(player1, gameStats.screenWidth);
				CheckCollisionBallArena(ball, player1.playerLives, gameStats.gameStatus, gameStats);
				CheckCollisionBallPlayer(ball, player1.playerRec);
				CheckBrickBallStatus(ball, gameBrick, maxBricks, player1.playerPoints);
				CheckPlayerWinStatus(player1, gameStats.gameStatus);
				UpdatePlayer(player1);
				UpdateBall(ball, gameStats, player1.playerRec.recPos.x, player1.playerRec.recPos.y);
			}
			break;

		case SceneStatus::GAMEPAUSE:

			if (slGetKey(SL_KEY_ENTER) && gameStats.gameStatus == SceneStatus::GAMEPAUSE)
			{
				gameStats.gameStatus = SceneStatus::GAMEPLAY;
			}
			break;

		case SceneStatus::RESETGAME:

			InitPlayer(player1, gameStats.gameStatus);
			InitBrick(gameBrick, maxBricks, gameStats);
			InitBall(ball);
			gameStats.gameStatus = SceneStatus::GAMEPAUSE;
			break;

		case SceneStatus::GAMEEND:

			if (slGetKey(SL_KEY_ENTER))
			{
				gameStats.gameStatus = SceneStatus::RESETGAME;
				player1.gameEnd = true;
			}
			break;

		default:
			break;
		}
	}

	void Draw(Player player1, Ball& ball, GameStats& gameStats, Brick gameBrick[])
	{
		int auxPosXPlayer1 = 200;

		switch ((SceneStatus)gameStats.gameStatus)
		{
		case SceneStatus::FIRSTGAME:
			PrintScore(player1.playerPoints, gameStats);
			PrintLives(player1.playerLives, gameStats);
			DrawBrick(gameBrick, maxBricks);
			DrawPlayer(player1);
			DrawBall(ball);
			break;

		case SceneStatus::GAMEPLAY:

			PrintScore(player1.playerPoints, gameStats);
			PrintLives(player1.playerLives, gameStats);
			DrawBrick(gameBrick, maxBricks);
			DrawPlayer(player1);
			DrawBall(ball);
			break;

		case SceneStatus::GAMEPAUSE:

			PrintScore(player1.playerPoints, gameStats);
			PrintLives(player1.playerLives, gameStats);
			DrawBrick(gameBrick, maxBricks);
			DrawPlayer(player1);
			DrawBall(ball);
			//PrintPause();
			//PrintRules();
			//PrintCredits();
			break;

		case SceneStatus::GAMEEND:

			//PrintEndMatchMsg(player1.playerPoints, player2.playerPoints, gameStats.gameManager);
			PrintScore(player1.playerPoints, gameStats);
			PrintLives(player1.playerLives, gameStats);
			DrawPlayer(player1);
			DrawBall(ball);
			break;

		default:
			break;
		}
	}

	void DeInit(GameStats& gameStats)
	{
		switch ((SceneStatus)gameStats.gameStatus)
		{
		case SceneStatus::SIMEND:

			
			break;

		default:
			break;
		}
	}
}