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

	void RunGame()
	{
		srand(time(nullptr));
		gameStats.gameStatus = SceneStatus::INITGAME;

		Init(player1, ball, gameStats, bricks, buttons);

		while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
		{	
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
			gameStats.gameStatus = SceneStatus::GAMEEND;
		}
			break;

		default:
			break;
		}
	}

	void Update(Player& player1, GameStats& gameStats, Ball& ball, Brick gameBrick[], MenuButtons buttons)
	{
		gameStats.enterWasPressed = gameStats.enterIsPressed;
		gameStats.enterIsPressed = slGetKey(SL_KEY_ENTER);

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
			
			if (!gameStats.enterWasPressed && gameStats.enterIsPressed && gameStats.gameStatus == SceneStatus::GAMEPLAY)
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

			if (!gameStats.enterWasPressed && gameStats.enterIsPressed && gameStats.gameStatus == SceneStatus::GAMEPAUSE)
			{
				gameStats.gameStatus = SceneStatus::GAMEPLAY;
			}
			//en ambos casos pongo gameend en true asi al pasar por reset se reinician las stats
			else if (slGetKey('R') && gameStats.gameStatus == SceneStatus::GAMEPAUSE)
			{
				player1.gameEnd = true;
				gameStats.isResetMatch = true;
				gameStats.gameStatus = SceneStatus::RESETGAME;
			}
			else if (slGetKey('M') && gameStats.gameStatus == SceneStatus::GAMEPAUSE)
			{
				gameStats.gameStatus = SceneStatus::RESETGAME;
				player1.gameEnd = true;
				gameStats.goMenu = true;
			}
			break;

		case SceneStatus::RESETGAME:
			
			InitBrick(gameBrick, maxBricks, gameStats, player1.gameEnd);
			InitBall(ball);
			InitPlayer(player1, gameStats.gameStatus);
			//en caso de volver a menu desde gameplay reset de stats y al menu
			if (gameStats.goMenu == true)
			{
				gameStats.gameStatus = SceneStatus::GAMEMENU;
				gameStats.goMenu = false;
			}
			//en caso de querer hacer reset, reset de stats y a firstgame para juego nuevo
			else if(gameStats.isResetMatch == true)
			{
				gameStats.gameStatus = SceneStatus::FIRSTGAME;
				gameStats.isResetMatch = false;
			}
			else
			{
				gameStats.gameStatus = SceneStatus::GAMEPAUSE;
			}
			break;

		case SceneStatus::GAMEEND:

			//en caso de muerte o victoria reset de stats
			if (slGetKey(SL_KEY_ENTER))
			{
				player1.gameEnd = true;
				gameStats.gameStatus = SceneStatus::RESETGAME;
			}
			else if (slGetKey('M'))
			{
				gameStats.gameStatus = SceneStatus::RESETGAME;
				player1.gameEnd = true;
				gameStats.goMenu = true;
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
			DrawPause(gameStats);
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
			DrawPause(gameStats);
			break;

		case SceneStatus::GAMEEND:

			PrintScore(player1.playerPoints, gameStats);
			PrintLives(player1.playerLives, gameStats);
			DrawBrick(gameBrick, maxBricks, gameStats);
			DrawPlayer(player1);
			DrawBall(ball);
			DrawPause(gameStats);
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