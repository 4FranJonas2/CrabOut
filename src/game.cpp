#include "game.h"

#include <iostream>
#include "sl.h"

#include "objects/player.h"
#include "objects/ball.h"
#include "scenes/gameUI.h"
#include "objects/brick.h"
#include "scenes/menu.h"
#include "objects/powerUp.h"

//toma power up
//Sound Effect by <a href = "https://pixabay.com/es/users/r0t0r-34451638/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=151672">R0T0R< / a> from <a href = "https://pixabay.com//?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=151672">Pixabay< / a>

//lcick en boton
//Sound Effect by <a href = "https://pixabay.com/es/users/freesound_community-46691455/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=99630">freesound_community< / a> from <a href = "https://pixabay.com/sound-effects//?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=99630">Pixabay< / a>

//rebote
//Sound Effect by <a href = "https://pixabay.com/es/users/freesound_community-46691455/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=82881">freesound_community< / a> from <a href = "https://pixabay.com//?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=82881">Pixabay< / a>
using namespace std;

namespace crabOut
{
	const int maxBricks = 30;
	const 	int maxPowers = 9;

	float lastPowerTime = 0.0;
	float powerCooldown = 6.0f;
	bool hit;

	GameStats gameStats;
	Player player1;
	Ball ball;
	Brick bricks[maxBricks];
	MenuButtons buttons;
	PowerUp powers[maxPowers];
	Vector2 auxBrickHit;


	static void Init(Player& player1, Ball& ball, GameStats& gameStats, Brick brick[], MenuButtons& buttons, Vector2& auxBrickHit);
	static void Update(Player& player1, GameStats& gameStats, Ball& ball, Brick brick[], MenuButtons buttons, PowerUp powers[], Vector2& auxBrickHit);
	static void Draw(Player player1, Ball& ball, GameStats& gameStats, Brick brick[], MenuButtons buttons);
	static void InitTextures(GameStats& gameTextures);
	static void DeInit(GameStats& gameStats);

	void RunGame()
	{
		srand(time(nullptr));
		gameStats.gameStatus = SceneStatus::INITGAME;

		Init(player1, ball, gameStats, bricks, buttons,auxBrickHit);

		while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
		{	
			Update(player1, gameStats, ball, bricks, buttons, powers,auxBrickHit);

			Draw(player1, ball, gameStats, bricks, buttons);
			
			slRender();
		}
		slClose();
	}

	static void Init(Player& player1, Ball& ball, GameStats& gameStats, Brick gameBrick[], MenuButtons& buttons, Vector2& auxBrickHit)
	{
		switch ((SceneStatus)gameStats.gameStatus)
		{
		case SceneStatus::INITGAME:
		{
			// set up our window and a few resources we need
			slWindow(gameStats.screenWidth, gameStats.screenHeight, "CrabOut", false);
			InitTextures(gameStats);
			InitButtons(buttons);
			InitPlayer(player1, gameStats.gameStatus);
			InitBrick(gameBrick, maxBricks, gameStats, player1.gameEnd);
			InitBall(ball);

			auxBrickHit.x = 0.0;
			auxBrickHit.y = 0.0;

			int font = slLoadFont("res/dogicapixel.ttf");
			slSetFont(font, gameStats.fontSize);

			gameStats.gameStatus = SceneStatus::GAMEMENU;
		}
			break;

		default:
			break;
		}
	}

	static void Update(Player& player1, GameStats& gameStats, Ball& ball, Brick gameBrick[], MenuButtons buttons, PowerUp powers[], Vector2& auxBrickHit)
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

			if (slGetKey('M'))
			{
				gameStats.gameStatus = SceneStatus::RESETGAME;
				player1.gameEnd = true;
				gameStats.goMenu = true;
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
				CheckBrickBallStatus(ball, gameBrick, maxBricks, player1.playerPoints, auxBrickHit, hit);
				CreatePowerUp(powers, auxBrickHit, hit);
				CheckPlayerWinStatus(player1, gameStats.gameStatus);
				UpdatePowerUp(powers, player1.playerRec,player1.playerVel,player1.powerActive, lastPowerTime);
				UpdatePlayer(player1);
				UpdateBall(ball, gameStats, player1.playerRec.recPos.x, player1.playerRec.recPos.y);
				PowersCleaner(player1,powerCooldown,lastPowerTime);

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
			ResetPowerUps(powers,gameStats,auxBrickHit,hit);
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

	static void Draw(Player player1, Ball& ball, GameStats& gameStats, Brick gameBrick[], MenuButtons buttons)
	{

		switch ((SceneStatus)gameStats.gameStatus)
		{
		case SceneStatus::FIRSTGAME:
			slSprite(gameStats.backGroundImage, gameStats.screenWidth / 2, gameStats.screenHeight / 2, gameStats.screenWidth, gameStats.screenHeight);

			gamePlayUi(player1.playerLives, player1.playerPoints, gameStats);
			DrawBrick(gameBrick, maxBricks, gameStats);
			DrawPause(gameStats);
			DrawPlayer(player1);
			DrawBall(ball, gameStats);
			break;

		case SceneStatus::GAMEMENU:
			slSprite(gameStats.backGroundImage, gameStats.screenWidth / 2, gameStats.screenHeight / 2, gameStats.screenWidth, gameStats.screenHeight);
			slSprite(gameStats.coconutTree, gameStats.screenWidth / 2, gameStats.screenHeight / 2, gameStats.screenWidth, gameStats.screenHeight);
		    DrawMainMenu( gameStats, buttons);

			break;

		case SceneStatus::GAMERULES:
			slSprite(gameStats.backGroundImage, gameStats.screenWidth / 2, gameStats.screenHeight / 2, gameStats.screenWidth, gameStats.screenHeight);

			DrawRulesMenu(gameStats, buttons);

			break;

		case SceneStatus::GAMECREDITS:
			slSprite(gameStats.backGroundImage, gameStats.screenWidth / 2, gameStats.screenHeight / 2, gameStats.screenWidth, gameStats.screenHeight);

			DrawCreditsMenu(gameStats, buttons);
			break;

		case SceneStatus::GAMEPLAY:
			slSprite(gameStats.backGroundImage, gameStats.screenWidth / 2, gameStats.screenHeight / 2, gameStats.screenWidth, gameStats.screenHeight);

			gamePlayUi(player1.playerLives, player1.playerPoints, gameStats);
			DrawBrick(gameBrick, maxBricks,gameStats);
			DrawPlayer(player1);
			DrawPowerUp(powers, gameStats);
			DrawBall(ball, gameStats);
			break;

		case SceneStatus::GAMEPAUSE:
			slSprite(gameStats.backGroundImage, gameStats.screenWidth / 2, gameStats.screenHeight / 2, gameStats.screenWidth, gameStats.screenHeight);

			gamePlayUi(player1.playerLives, player1.playerPoints, gameStats);
			DrawBrick(gameBrick, maxBricks, gameStats);
			DrawPlayer(player1);
			DrawPowerUp(powers, gameStats);
			DrawBall(ball, gameStats);
			DrawPause(gameStats);
			break;

		case SceneStatus::GAMEEND:
			slSprite(gameStats.backGroundImage, gameStats.screenWidth / 2, gameStats.screenHeight / 2, gameStats.screenWidth, gameStats.screenHeight);

			gamePlayUi(player1.playerLives, player1.playerPoints, gameStats);
			DrawBrick(gameBrick, maxBricks, gameStats);
			DrawPlayer(player1);
			DrawPowerUp(powers,gameStats);
			DrawBall(ball,gameStats);
			DrawPause(gameStats);
			break;

		default:
			break;
		}
	}
	static void InitTextures(GameStats& gameTextures)
	{
		gameStats.backGroundImage = slLoadTexture("res/fondoPlaya.png");
		gameStats.coconut = slLoadTexture("res/coconut.png");
		gameStats.redCoconut = slLoadTexture("res/redCoconut.png");
		gameStats.yellowCoconut = slLoadTexture("res/yellowCoconut.png");
		gameStats.greenCoconut = slLoadTexture("res/greenCoconut.png");
		gameStats.coconutTree = slLoadTexture("res/menuTree.png");
	}

	static void DeInit(GameStats& gameStats)
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