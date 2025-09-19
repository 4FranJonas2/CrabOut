#include "gameUI.h"

namespace pong2
{
	void PrintScore(int playerScore, int posX)
	{
		DrawText(TextFormat("%i",playerScore), posX, 200, 60, GRAY);
	}

	void PrintArena(int screenWidth, int screenHeight)
	{
		DrawLine((screenWidth / 2), 0, (screenWidth / 2), screenHeight, GRAY);
	}

	void PrintPause()
	{
		int textFont = 30;
		Color textColor = WHITE;

		DrawText("GAME PAUSE", 305, 50, textFont, textColor);
		DrawText("Press SPACEBAR", 265, 300, textFont, textColor);
		DrawText("To Continue", 310, 350, textFont, textColor);
	}

	void PrintEndMatchMsg(int player1Score, int player2Score, SceneStatus& gameScene)
	{
		int textFont = 30;
		Color textColor = WHITE;
		int winScore = 3;
		int auxPosXP1 = 100;
		int auxPosXP2 = 500;
		int auxPosXP3 = 40;
		int auxPosY = 100;
		int auxPosY2 = 300;

		if (player1Score == winScore)
		{
			DrawText("Player 1 WINS ", auxPosXP1, auxPosY, textFont, textColor);
			DrawText("Player 2  LOSE ", auxPosXP2, auxPosY, textFont, textColor);
			DrawText("Press ENTER to Restart or ESC to leave game ", auxPosXP3, auxPosY2, textFont, textColor);
		}

		if (player2Score == winScore)
		{
			DrawText("Player 1 LOSE ", auxPosXP1, auxPosY, textFont, textColor);
			DrawText("Player 2  WINS ", auxPosXP2, auxPosY, textFont, textColor);
			DrawText("Press ENTER to Restart or ESC to leave game ", auxPosXP3, auxPosY2, textFont, textColor);
		}
	}

	void PrintRules()
	{
		int textFont = 30;
		Color textColor = GRAY;
		int auxPosX1 = 135;
		int auxPosX2 = 120;
		int auxPosY1 = 100;
		int auxPosY2 = 150;

		DrawText("Player 1 use W and S key to MOVE", auxPosX1, auxPosY1, textFont, textColor);
		DrawText("Player 2 use ARROW KEYS to MOVE", auxPosX2, auxPosY2, textFont, textColor);
	}

	void PrintCredits()
	{
		int textFont = 0;
		int auxPosX1 = 0;
		int auxPosY1 = 440;

		DrawText(" PONGOSO a remastered version of PONG by Francisco Jonas",
			auxPosX1, auxPosY1, textFont, GRAY);
	}
}