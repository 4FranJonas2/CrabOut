#include "player.h"

namespace pong2
{
	void InitPlayer(Player& player, float initPlayerPosX, SceneStatus initGame)
	{
		//default stats for player
		int winScore = 3;
		int playerRecWidth = 15;
		int playerRecHeight = 100;
		float initPlayerPosY = 225;

		player.playerColor = BROWN;

		if (initGame == SceneStatus::INITGAME || player.gameEnd)
		{
			player.playerLives = 3;
			player.playerPoints = 0;
			player.gameEnd = false;
		}
		player.playerVel = 300.0f;
		player.playerRec.x = initPlayerPosX;
		player.playerRec.y = initPlayerPosY - (playerRecHeight/2);
		player.playerRec.width = playerRecWidth;
		player.playerRec.height = playerRecHeight;
	}

	void UpdatePlayer(Player& player, KeyboardKey key1, KeyboardKey key2)
	{
		//movimiento 
		//arriba
		if (IsKeyDown(key1))
		{
			player.playerRec.y -= player.playerVel * GetFrameTime();
		}
		//abajo
		if (IsKeyDown(key2))
		{
			player.playerRec.y += player.playerVel * GetFrameTime();
		}
	}

	void DrawPlayer(Player player)
	{
		DrawRectangle(player.playerRec.x, player.playerRec.y, player.playerRec.width,
			player.playerRec.height, player.playerColor);
	}

	void CheckPlayerPoints(int player1Points,int player2Points, SceneStatus& gameStatus)
	{
 		int winScore = 3;
		
		if (player1Points >= winScore || player2Points >= winScore)
		{
			gameStatus = SceneStatus::GAMEEND;
		}
	}
	void CheckPlayerColisionArena(Player& player, int screenHeight)
	{
		if (player.playerRec.y <= 0)
		{
			player.playerRec.y = 0;
		}
		if (player.playerRec.y + player.playerRec.height >= screenHeight)
		{
			player.playerRec.y = screenHeight - player.playerRec.height;
		}
	}
}