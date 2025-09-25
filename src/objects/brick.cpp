#include "brick.h"

namespace crabOut
{
	void InitBrick(Brick gameBricks[], int maxBricks, Pong gameStats)
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

				gameBricks[brickCounter].brickColor.r = 0.6;
				gameBricks[brickCounter].brickColor.g = 0.3;
				gameBricks[brickCounter].brickColor.b = 0.3;

				brickCounter++;
			}
		}
	}

	void DrawBrick(Brick gameBricks[], int maxBricks)
	{
		for (int i = 0; i < maxBricks; i++)
		{
			slSetForeColor(gameBricks[i].brickColor.r, gameBricks[i].brickColor.g, gameBricks[i].brickColor.b, 1.0);
			slRectangleFill(gameBricks[i].brickRec.recPos.x, gameBricks[i].brickRec.recPos.y,
				gameBricks[i].brickRec.recSize.x, gameBricks[i].brickRec.recSize.y);
		}
	}

}
