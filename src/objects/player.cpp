#include "player.h"

namespace crabOut
{
	void InitPlayer(Player& player, SceneStatus initGame)
	{
		//default stats for player
		int winScore = 3;
		int playerRecWidth = 100;
		int playerRecHeight = 20;
		float initPlayerPosX = 400;
		float initPlayerPosY = 15;

		//rojo
		player.playerColor.r = 1.0;
		player.playerColor.g= 0.3;
		player.playerColor.b = 0.1;
		player.playerColor.a = 1.0;

		if (initGame == SceneStatus::INITGAME || player.gameEnd)
		{
			player.playerLives = 3;
			player.playerPoints = 0;
			player.gameEnd = false;
		}

		player.playerVel = 300.0f;
		player.playerRec.recPos.x = initPlayerPosX;
		player.playerRec.recPos.y = initPlayerPosY;
		player.playerRec.recSize.x = playerRecWidth;
		player.playerRec.recSize.y = playerRecHeight;
	}

	void UpdatePlayer(Player& player)
	{
		//movimiento 
		//izquierda
		if (slGetKey('A'))
		{
			player.playerRec.recPos.x -= player.playerVel * slGetDeltaTime();
		}
		//derecha
		if (slGetKey('D'))
		{
			player.playerRec.recPos.x += player.playerVel * slGetDeltaTime();
		}
	}
	 
	void CheckPlayerPoints(int player1Points, SceneStatus& gameStatus)
	{
 		int winScore = 3;
		
		if (player1Points >= winScore)
		{
			gameStatus = SceneStatus::GAMEEND;
		}
	}
	void CheckPlayerColisionArena(Player& player, int screenWidth)
	{
		if (player.playerRec.recPos.x - player.playerRec.recSize.x /2 <= 0)
		{
			player.playerRec.recPos.x =0 + player.playerRec.recSize.x /2;
		}
		if (player.playerRec.recPos.x + player.playerRec.recSize.x/2 >= screenWidth)
		{
			player.playerRec.recPos.x = screenWidth - player.playerRec.recSize.x /2;
		}
	}

	void DrawPlayer(Player player)
	{
		slSetForeColor(player.playerColor.r, player.playerColor.g, player.playerColor.b, player.playerColor.a);
		slRectangleFill(player.playerRec.recPos.x, player.playerRec.recPos.y,
			player.playerRec.recSize.x, player.playerRec.recSize.y);
	}
}