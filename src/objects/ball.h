#pragma once

#include "sl.h"

#include "..\utilities.h"

namespace crabOut
{
	struct Circle
	{
		Vector2 pos;
		float rad;
	};

	enum class BallDir
	{
		UPRIGHT=1,
		UPLEFT,
		DOWNRIGHT,
		DOWNLEFT
	};

	struct Ball
	{
		Vector2 ballSize;
		Vector2 ballSpeed;
		Circle ballCircle;
		Colors ballColor;
		float ballVel;
		int frameCounter;
	};

	void InitBall(Ball& ball);
	void UpdateBall(Ball& ball, Pong gameStatus, int playerPosX, int playerPosY);
	bool CheckCollisionBallPlayer(Ball& ball, Rectangle playerRec);
	void CheckCollisionBallArena(Ball& ball, int& player1Points, SceneStatus& resetPoint, Pong gameStats);
	void DrawBall(Ball& ball);
}


