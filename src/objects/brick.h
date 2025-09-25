#pragma once

#include "sl.h"

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
	//void UpdatePlayer();
	//void CheckPlayerPoints();
	//void CheckBrickBallCollision();
	void DrawBrick(Brick gameBricks[], int maxBricks);
}
