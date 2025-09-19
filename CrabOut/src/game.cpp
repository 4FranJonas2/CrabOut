#include "game.h"

#include <iostream>

using namespace std;

namespace pong2
{
	void GamePlay()
	{
		srand(time(nullptr));
		Pong gameStats;
		Player player1;
		Player player2;
		Ball ball;

		gameStats.gameManager = SceneStatus::INITGAME;

		Init(player1, player2, ball, gameStats);

		while (!WindowShouldClose())
		{
			Update(player1, player2, gameStats, ball);

			BeginDrawing();

			ClearBackground(BLACK);
			Draw(player1, player2, ball, gameStats);

			EndDrawing();
		}

		CloseWindow();
	}

	void Init(Player& player1, Player& player2, Ball& ball, Pong& gameStats)
	{
		switch ((SceneStatus)gameStats.gameManager)
		{
		case SceneStatus::INITGAME:
			InitWindow(gameStats.screenWidth, gameStats.screenHeight, "PongOso");
			InitPlayer(player1, player1.initPlayer1PosX,gameStats.gameManager);
			InitPlayer(player2, player2.initPlayer2PosX, gameStats.gameManager);
			InitBall(ball);
			gameStats.gameManager = SceneStatus::GAMEPAUSE;
			break;
		default:
			break;
		}
	}

	void Update(Player& player1, Player& player2, Pong& gameStats, Ball& ball)
	{
		switch ((SceneStatus)gameStats.gameManager)
		{
		case SceneStatus::GAMEPLAYTWOPLAYERS:

			bool ballIsHitP1;
			bool ballIsHitP2;

			if (IsKeyPressed(KEY_SPACE) && gameStats.gameManager == SceneStatus::GAMEPLAYTWOPLAYERS)
			{
				gameStats.gameManager = SceneStatus::GAMEPAUSE;
			}

			if (gameStats.gameManager == SceneStatus::GAMEPLAYTWOPLAYERS)
			{
				UpdatePlayer(player1, KEY_W, KEY_S);
				UpdatePlayer(player2, KEY_UP, KEY_DOWN);
				CheckPlayerColisionArena(player1, gameStats.screenHeight);
				CheckPlayerColisionArena(player2, gameStats.screenHeight);
				CheckCollisionBallArena(ball, player1.playerPoints, player2.playerPoints, gameStats.gameManager);
				ballIsHitP1 = CheckCollisionBallPlayer(ball, player1.playerRec, player1.playerColor);
				ballIsHitP2 = CheckCollisionBallPlayer(ball, player2.playerRec, player2.playerColor);
				CheckPlayerPoints(player1.playerPoints, player2.playerPoints, gameStats.gameManager);
				UpdateBall(ball);
			}
			break;

		case SceneStatus::GAMEPAUSE:

			if (IsKeyPressed(KEY_SPACE) && gameStats.gameManager == SceneStatus::GAMEPAUSE)
			{
				gameStats.gameManager = SceneStatus::GAMEPLAYTWOPLAYERS;
			}
			break;

		case SceneStatus::RESETGAME:

			InitPlayer(player1, player1.initPlayer1PosX, gameStats.gameManager);
			InitPlayer(player2, player2.initPlayer2PosX, gameStats.gameManager);
			InitBall(ball);
			gameStats.gameManager = SceneStatus::GAMEPAUSE;
			break;

		case SceneStatus::GAMEEND:

			if (IsKeyPressed(KEY_ENTER))
			{
				gameStats.gameManager = SceneStatus::RESETGAME;
				player1.gameEnd = true;
				player2.gameEnd = true;
			}
			break;

		default:
			break;
		}
	}

	void Draw(Player player1, Player player2, Ball& ball, Pong& gameStats)
	{
		int auxPosXPlayer1 = 200;
		int auxPosXPlayer2 = 570;

		switch ((SceneStatus)gameStats.gameManager)
		{
		case SceneStatus::INITGAME:

			PrintScore(player1.playerPoints, auxPosXPlayer1);
			PrintScore(player2.playerPoints, auxPosXPlayer2);
			PrintArena(gameStats.screenWidth, gameStats.screenHeight);
			DrawPlayer(player1);
			DrawPlayer(player2);
			DrawBall(ball);
			PrintPause();
			PrintRules();
			PrintCredits();
			break;
	
		case SceneStatus::GAMEPLAYTWOPLAYERS:

			PrintScore(player1.playerPoints, auxPosXPlayer1);
			PrintScore(player2.playerPoints, auxPosXPlayer2);
			PrintArena(gameStats.screenWidth, gameStats.screenHeight);
			DrawPlayer(player1);
			DrawPlayer(player2);
			DrawBall(ball);
			break;

		case SceneStatus::GAMEPAUSE:

			PrintScore(player1.playerPoints, auxPosXPlayer1);
			PrintScore(player2.playerPoints, auxPosXPlayer2);
			PrintArena(gameStats.screenWidth, gameStats.screenHeight);
			DrawPlayer(player1);
			DrawPlayer(player2);
			DrawBall(ball);
			PrintPause();
			PrintRules();
			PrintCredits();
			break;

		case SceneStatus::GAMEEND:

			PrintEndMatchMsg(player1.playerPoints, player2.playerPoints, gameStats.gameManager);
			PrintScore(player1.playerPoints, auxPosXPlayer1);
			PrintScore(player2.playerPoints, auxPosXPlayer2);
			PrintArena(gameStats.screenWidth, gameStats.screenHeight);
			DrawPlayer(player1);
			DrawPlayer(player2);
			DrawBall(ball);
			break;

		default:
			break;
		}
	}
}