#include "player.h"

namespace crabOut
{
	float currentTime;

	void PowersCleaner(Player& player, float powerCoolDown, float lastPowerTime)
	{
		float currentTime = slGetTime();

		if (currentTime - lastPowerTime >= powerCoolDown)
		{
			player.playerVel = 390.0f;
			player.playerRec.recSize.x = 100;
			player.powerActive = false;
		}
	}

	void InitPlayer(Player& player, SceneStatus initGame)
	{
		//default stats for player
		int lives = 3;
		int playerRecWidth = 150;
		int playerRecHeight = 60;
		float initPlayerPosX = 400;
		float initPlayerPosY = 30;

		//rojo
		player.playerColor.r = 1.0;
		player.playerColor.g = 0.3;
		player.playerColor.b = 0.1;
		player.playerColor.a = 1.0;

		if (initGame == SceneStatus::INITGAME || player.gameEnd || initGame == SceneStatus::FIRSTGAME)
		{
			player.playerLives = lives;
			player.playerPoints = 0;
			player.gameEnd = false;
		}

		player.playerVel = 390.0f;
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

	void CheckPlayerWinStatus(Player player, SceneStatus& gameStatus)
	{
		if (player.playerLives == 0)
		{
			gameStatus = SceneStatus::GAMEEND;
		}
	}
	void CheckPlayerColisionArena(Player& player, int screenWidth)
	{
		if (player.playerRec.recPos.x - player.playerRec.recSize.x / 2 <= 0)
		{
			player.playerRec.recPos.x = 0 + player.playerRec.recSize.x / 2;
		}
		if (player.playerRec.recPos.x + player.playerRec.recSize.x / 2 >= screenWidth)
		{
			player.playerRec.recPos.x = screenWidth - player.playerRec.recSize.x / 2;
		}
	}

	bool IsPlayerAlive(Player player)
	{
		if (player.playerLives == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool HasPlayerReachMaxPoints(Player player)
	{
		int maxPoints = 900;

		if (player.playerPoints == maxPoints)
		{
			return false;
		}
		else
		{
			return true;
		}
	}




	void DrawPlayer(Player& player, GameStats& gamePlayer)
	{

		double t = slGetTime() - player.startTime;
		player.currentFrame = int(t / 0.2) % 3;

		if (slGetKey('A'))
		{
			slSetSpriteTiling(player.frameWidth, 1.0);
			slSetSpriteScroll(player.currentFrame * player.frameWidth, 0.0);
			slSprite(gamePlayer.crabNormalWalk, player.playerRec.recPos.x, player.playerRec.recPos.y, player.playerRec.recSize.x, player.playerRec.recSize.y);
			slSetSpriteTiling(1.0, 1.0);
			slSetSpriteScroll(0.0, 0.0);
		}
		//derecha
		else if (slGetKey('D'))
		{
			slSetSpriteTiling(player.frameWidth, 1.0);
			slSetSpriteScroll(player.currentFrame * player.frameWidth, 0.0);
			slSprite(gamePlayer.crabNormalWalk, player.playerRec.recPos.x, player.playerRec.recPos.y, player.playerRec.recSize.x, player.playerRec.recSize.y);
			slSetSpriteTiling(1.0, 1.0);
			slSetSpriteScroll(0.0, 0.0);
		}
		else
		{
			slSetSpriteTiling(player.frameWidth, 1.0);
			slSetSpriteScroll(player.currentFrame * player.frameWidth, 0.0);
			slSprite(gamePlayer.crabNormalWalk, player.playerRec.recPos.x, player.playerRec.recPos.y, player.playerRec.recSize.x, player.playerRec.recSize.y);
			slSetSpriteTiling(1.0, 1.0);
			slSetSpriteScroll(0.0, 0.0);


		}

	}
}