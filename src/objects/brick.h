#pragma once

#include "sl.h"

#include <cmath>
#include <algorithm>

#include "ball.h"
#include "../utilities.h"

namespace crabOut
{

	struct Brick
	{
		Rectangle brickRec;
		Colors brickColor;
		
		int brickLives;
		bool isBrickActive;
		bool gotHit;
	};

	void InitBrick(Brick gameBricks[], int maxBricks, Pong gameStats);
	void CheckBrickBallStatus(Ball& ball, Brick gameBricks[], int maxBriks, int& plyerPoints);
	void UpdateBrick(Brick brick[], int index);
	//void CheckPlayerPoints();
	//void CheckBrickBallCollision();
	void DrawBrick(Brick gameBricks[], int maxBricks);
}
