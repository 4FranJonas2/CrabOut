#include "player.h"

namespace crabOut
{
	void InitPlayer(Player& player, float initPlayerPosY, SceneStatus initGame)
	{
		//default stats for player
		int winScore = 3;
		int playerRecWidth = 15;
		int playerRecHeight = 100;
		float initPlayerPosX = 225;

		//rojo
		player.playerColor.r = 255;
		player.playerColor.g= 51;
		player.playerColor.b = 51;

		if (initGame == SceneStatus::INITGAME || player.gameEnd)
		{
			player.playerLives = 3;
			player.playerPoints = 0;
			player.gameEnd = false;
		}

		player.playerVel = 300.0f;
		player.playerRec.recPos.x = initPlayerPosX - (playerRecWidth / 2);
		player.playerRec.recPos.y = initPlayerPosY ;
		player.playerRec.recSize.x = playerRecWidth;
		player.playerRec.recSize.y = playerRecHeight;
	}

	void UpdatePlayer(Player& player, int key1, int key2)
	{
		//movimiento 
		//arriba
		if (key1)
		{
			player.playerRec.recPos.x -= player.playerVel * slGetDeltaTime();
		}
		//abajo
		if (key2)
		{
			player.playerRec.recPos.x += player.playerVel * slGetDeltaTime();
		}
	}

	void DrawPlayer(Player player)
	{
		slSetForeColor(player.playerColor.r, player.playerColor.g, player.playerColor.b, 10);
		slRectangleFill(player.playerRec.recPos.x, player.playerRec.recPos.y,
			player.playerRec.recSize.y, player.playerRec.recSize.x);
	}

	void CheckPlayerPoints(int player1Points, SceneStatus& gameStatus)
	{
 		int winScore = 3;
		
		if (player1Points >= winScore)
		{
			gameStatus = SceneStatus::GAMEEND;
		}
	}
	void CheckPlayerColisionArena(Player& player, int screenHeight)
	{
		if (player.playerRec.recPos.x <= 0)
		{
			player.playerRec.recPos.x = 0;
		}
		if (player.playerRec.recPos.x + player.playerRec.recSize.x >= screenHeight)
		{
			player.playerRec.recSize.x = screenHeight - player.playerRec.recSize.x;
		}
	}
}