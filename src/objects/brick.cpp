#include "brick.h"

namespace crabOut
{
	void InitBrick(Brick gameBricks[], int maxBricks, GameStats gameStats, bool gameEnd)
	{
		int cols = 6;
		int rows = 5;
		int brickWidth = 70;
		int brickHeight = 30;
		int auxSpaceX = 30;
		int auxSpaceY = 20;
		int startPosX = 130;
		int startPosY = 550;
		int brickCounter = 0;

		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < cols; col++)
			{
				if (brickCounter >= maxBricks)
				{
					break;
				}

				gameBricks[brickCounter].brickRec.recSize.x = brickWidth;
				gameBricks[brickCounter].brickRec.recSize.y = brickHeight;

				gameBricks[brickCounter].brickRec.recPos.x = startPosX + col * (brickWidth + auxSpaceX);
				gameBricks[brickCounter].brickRec.recPos.y = startPosY - row * (brickHeight + auxSpaceY);

				if (gameStats.gameStatus == SceneStatus::INITGAME || gameEnd == true)
				{
					gameBricks[brickCounter].brickColor.r = 0.6;
					gameBricks[brickCounter].brickColor.g = 0.3;
					gameBricks[brickCounter].brickColor.b = 0.3;
					gameBricks[brickCounter].brickColor.a = 1.0;

					gameBricks[brickCounter].brickLives = 3;
					gameBricks[brickCounter].isBrickActive = true;
					gameBricks[brickCounter].gotHit = false;
				}

				brickCounter++;
			}
		}
	}

	void CheckBrickBallStatus(Ball& ball, Brick gameBricks[], int maxBriks, int& plyerPoints)
	{
		for (int i = 0; i < maxBriks; i++)
		{
			//si ladrillo tiene vidas lo analizo
			if (gameBricks[i].brickLives > 0)
			{

				float left = gameBricks[i].brickRec.recPos.x - gameBricks[i].brickRec.recSize.x / 2;
				float right = gameBricks[i].brickRec.recPos.x + gameBricks[i].brickRec.recSize.x / 2;
				float top = gameBricks[i].brickRec.recPos.y - gameBricks[i].brickRec.recSize.y / 2;
				float bottom = gameBricks[i].brickRec.recPos.y + gameBricks[i].brickRec.recSize.y / 2;

				if (ball.ballCircle.pos.x + ball.ballCircle.rad >= left &&
					ball.ballCircle.pos.x - ball.ballCircle.rad <= right &&
					ball.ballCircle.pos.y + ball.ballCircle.rad >= top &&
					ball.ballCircle.pos.y - ball.ballCircle.rad <= bottom)
				{
					float overlapLeft = fabs((ball.ballCircle.pos.x + ball.ballCircle.rad) - left);
					float overlapRight = fabs(right - (ball.ballCircle.pos.x - ball.ballCircle.rad));
					float overlapTop = fabs((ball.ballCircle.pos.y + ball.ballCircle.rad) - top);
					float overlapBottom = fabs(bottom - (ball.ballCircle.pos.y - ball.ballCircle.rad));

					float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

					if (minOverlap == overlapLeft)
					{
						ball.ballCircle.pos.x = left - ball.ballCircle.rad;
						ball.ballSpeed.x *= -1;

						UpdateBrick(gameBricks, i, plyerPoints);
					}
					else if (minOverlap == overlapRight)
					{
						ball.ballCircle.pos.x = right + ball.ballCircle.rad;
						ball.ballSpeed.x *= -1;

						UpdateBrick(gameBricks, i, plyerPoints);
					}
					else if (minOverlap == overlapTop)
					{
						ball.ballCircle.pos.y = top - ball.ballCircle.rad;
						ball.ballSpeed.y *= -1;

						UpdateBrick(gameBricks, i, plyerPoints);
					}
					else if (minOverlap == overlapBottom)
					{
						ball.ballCircle.pos.y = bottom + ball.ballCircle.rad;
						ball.ballSpeed.y *= -1;

						UpdateBrick(gameBricks, i, plyerPoints);
					}
				}

			}
			//si es golpeado se opaca mas y mas 
			if (gameBricks[i].gotHit == true)
			{
				gameBricks[i].gotHit = false;
				gameBricks[i].brickColor.a -= 0.3;
			}
			//si no tiene vidas lo opaco y declaro muerto
			if (gameBricks[i].brickLives == 0)
			{
				gameBricks[i].isBrickActive = false;
				gameBricks[i].brickColor.r = 0.0;
				gameBricks[i].brickColor.g = 0.0;
				gameBricks[i].brickColor.b = 0.0;
				gameBricks[i].brickColor.a = 0.0;
			}
		}
	}

	void UpdateBrick(Brick brick[], int index, int& playerPoints)
	{
		brick[index].brickLives--;
		brick[index].gotHit = true;
		playerPoints += 10;
	}

	void DrawBrick(Brick gameBricks[], int maxBricks, GameStats gameStats)
	{
		/*if (true)
		{

		}*/

		for (int i = 0; i < maxBricks; i++)
		{
			slSetForeColor(gameBricks[i].brickColor.r, gameBricks[i].brickColor.g, gameBricks[i].brickColor.b, gameBricks[i].brickColor.a);
			slRectangleFill(gameBricks[i].brickRec.recPos.x, gameBricks[i].brickRec.recPos.y,
				gameBricks[i].brickRec.recSize.x, gameBricks[i].brickRec.recSize.y);
		}
	}

}
