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
		float auxBrickAlpha;
		bool isBrickActive;
		bool gotHit;
	};

	void InitBrick(Brick gameBricks[], int maxBricks, GameStats gameStats, bool gameEnd);
	void CheckBrickBallStatus(Ball& ball, Brick gameBricks[], int maxBriks, int& plyerPoints, Vector2& brikcHitPos, bool& brickGotHit);
	void UpdateBrick(Brick brick[], int index, int& playerPoints);
	void DrawBrick(Brick gameBricks[], int maxBricks, GameStats gameStats);
}
