#include "game.h"

#include "sl.h"

#include "objects/player.h"
#include "objects/ball.h"
#include "scenes/gameUI.h"
#include "objects/brick.h"
#include "scenes/menu.h"

#include <iostream>

using namespace std;

namespace crabOut
{
	const int maxBricks = 30;
	GameStats gameStats;
	Player player1;
	Ball ball;
	Brick bricks[maxBricks];
	MenuButtons buttons;

	static void Init(Player& player1, Ball& ball, GameStats& gameStats, Brick brick[], MenuButtons& buttons);
	static void Update(Player& player1, GameStats& gameStats, Ball& ball, Brick brick[], MenuButtons buttons);
	static void Draw(Player player1, Ball& ball, GameStats& gameStats, Brick brick[], MenuButtons buttons);
	static void DeInit(GameStats& gameStats);

	bool enterIsPressed = false;
	bool enterWasPressed = false;
	
	void RunGame()
	{
		srand(time(nullptr));
		gameStats.gameStatus = SceneStatus::INITGAME;

		Init(player1, ball, gameStats, bricks, buttons);

		while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
		{
			enterWasPressed = enterIsPressed;
			enterIsPressed = slGetKey(SL_KEY_ENTER);

			Update(player1, gameStats, ball, bricks, buttons);

			Draw(player1, ball, gameStats, bricks, buttons);
			
			slRender();
		}
		slClose();
	}

	void Init(Player& player1, Ball& ball, GameStats& gameStats, Brick gameBrick[], MenuButtons& buttons)
	{
		switch ((SceneStatus)gameStats.gameStatus)
		{
		case SceneStatus::INITGAME:
		{
			// set up our window and a few resources we need
			slWindow(gameStats.screenWidth, gameStats.screenHeight, "CrabOut", false);

			InitButtons(buttons);
			InitPlayer(player1, gameStats.gameStatus);
			InitBrick(gameBrick, maxBricks, gameStats, player1.gameEnd);
			InitBall(ball);

			int font = slLoadFont("res/dogicapixel.ttf");
			slSetFont(font, gameStats.fontSize);
			gameStats.gameStatus = SceneStatus::GAMECREDITS;
		}
			break;

		default:
			break;
		}
	}

	void Update(Player& player1, GameStats& gameStats, Ball& ball, Brick gameBrick[], MenuButtons buttons)
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
				UpdatePlayer(player1);
				UpdateBall(ball, gameStats, player1.playerRec.recPos.x, player1.playerRec.recPos.y);
			}
			break;

		case SceneStatus::GAMEMENU:
			UpdateSceneMenus(gameStats, buttons);
			break;

		case SceneStatus::GAMERULES:
			UpdateSceneMenus(gameStats, buttons);
			break;

		case SceneStatus::GAMECREDITS:
			UpdateSceneMenus(gameStats, buttons);
			break;

		case SceneStatus::GAMEPLAY:
			
			if (!enterWasPressed && enterIsPressed && gameStats.gameStatus == SceneStatus::GAMEPLAY)
			{
				gameStats.gameStatus = SceneStatus::GAMEPAUSE;
			}

			if (gameStats.gameStatus == SceneStatus::GAMEPLAY)
			{
				CheckPlayerColisionArena(player1, gameStats.screenWidth);
				CheckCollisionBallArena(ball, player1.playerLives, gameStats);
				CheckCollisionBallPlayer(ball, player1.playerRec);
				CheckBrickBallStatus(ball, gameBrick, maxBricks, player1.playerPoints);
				CheckPlayerWinStatus(player1, gameStats.gameStatus);
				UpdatePlayer(player1);
				UpdateBall(ball, gameStats, player1.playerRec.recPos.x, player1.playerRec.recPos.y);

				if (!IsPlayerAlive(player1))
				{
					gameStats.gameStatus = SceneStatus::GAMEEND;
				}
				if (!HasPlayerReachMaxPoints(player1))
				{
					gameStats.gameStatus = SceneStatus::GAMEEND;
				}
			}
			break;

		case SceneStatus::GAMEPAUSE:

			if (!enterWasPressed && enterIsPressed && gameStats.gameStatus == SceneStatus::GAMEPAUSE)
			{
				gameStats.gameStatus = SceneStatus::GAMEPLAY;
			}
			break;

		case SceneStatus::RESETGAME:

			player1.gameEnd = true;
			InitBrick(gameBrick, maxBricks, gameStats, player1.gameEnd);
			InitBall(ball);
			InitPlayer(player1, gameStats.gameStatus);
			gameStats.gameStatus = SceneStatus::GAMEPAUSE;
			break;

		case SceneStatus::GAMEEND:

			if (slGetKey(SL_KEY_ENTER))
			{
				gameStats.gameStatus = SceneStatus::RESETGAME;
			}
			break;

		default:
			break;
		}
	}

	void Draw(Player player1, Ball& ball, GameStats& gameStats, Brick gameBrick[], MenuButtons buttons)
	{
		switch ((SceneStatus)gameStats.gameStatus)
		{
		case SceneStatus::FIRSTGAME:
			PrintScore(player1.playerPoints, gameStats);
			PrintLives(player1.playerLives, gameStats);
			DrawBrick(gameBrick, maxBricks, gameStats);
			PrintPause(gameStats);
			DrawPlayer(player1);
			DrawBall(ball);
			break;

		case SceneStatus::GAMEMENU:
		    DrawMainMenu( gameStats, buttons);

			break;

		case SceneStatus::GAMERULES:
			DrawRulesMenu(gameStats, buttons);

			break;

		case SceneStatus::GAMECREDITS:
			DrawCreditsMenu(gameStats, buttons);
			break;

		case SceneStatus::GAMEPLAY:

			PrintScore(player1.playerPoints, gameStats);
			PrintLives(player1.playerLives, gameStats);
			DrawBrick(gameBrick, maxBricks,gameStats);
			DrawPlayer(player1);
			DrawBall(ball);
			break;

		case SceneStatus::GAMEPAUSE:

			PrintScore(player1.playerPoints, gameStats);
			PrintLives(player1.playerLives, gameStats);
			DrawBrick(gameBrick, maxBricks, gameStats);
			DrawPlayer(player1);
			DrawBall(ball);
			PrintPause(gameStats);
			break;

		case SceneStatus::GAMEEND:

			PrintScore(player1.playerPoints, gameStats);
			PrintLives(player1.playerLives, gameStats);
			DrawBrick(gameBrick, maxBricks, gameStats);
			DrawPlayer(player1);
			DrawBall(ball);
			PrintPause(gameStats);
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