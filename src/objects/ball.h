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

	void InitBall(Ball& ball, int screenWidth, int screenHeight);
	void UpdateBall(Ball& ball);
	bool CheckCollisionBallPlayer(Ball& ball, Rectangle playerRec);
	void CheckCollisionBallArena(Ball& ball, int& player1Points, SceneStatus& resetPoint, int screenWidth, int screenHeight);
	void DrawBall(Ball& ball);
}


