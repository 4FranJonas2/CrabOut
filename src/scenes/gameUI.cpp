#include "gameUI.h"

using namespace std;

namespace crabOut
{
	Colors white = { 1.0f,1.0f,1.0f,1.0f };
	
	void PrintScore(int playerScore, GameStats gameStats)
	{
		float textPosX = 15.0;
		float textPosY = gameStats.screenHeight-20.0;
		string scoreText = "Score: " + to_string(playerScore);
		slSetForeColor(white.r, white.g, white.b,white.a);
		slText(textPosX, textPosY, scoreText.c_str());
	}

	void PrintLives(int playerLives, GameStats gameStats)
	{
		float textPosX = gameStats.screenWidth - 100.0;
		float textPosY = gameStats.screenHeight - 20.0;
		slSetForeColor(white.r, white.g, white.b, white.a);
		string scoreText = "Lives: " + to_string(playerLives);
		slText(textPosX, textPosY, scoreText.c_str());
	}

	/*void PrintPause()
	{
		int textFont = 30;
		Color textColor = WHITE;

		DrawText("GAME PAUSE", 305, 50, textFont, textColor);
		DrawText("Press P key", 265, 300, textFont, textColor);
		DrawText("To Continue", 310, 350, textFont, textColor);
	}*/

	/*void PrintEndMatchMsg(int player1Score, int player2Score, SceneStatus& gameScene)
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
	}*/

	/*void PrintCredits()
	{
		int textFont = 0;
		int auxPosX1 = 0;
		int auxPosY1 = 440;

		DrawText(" PONGOSO a remastered version of PONG by Francisco Jonas",
			auxPosX1, auxPosY1, textFont, GRAY);
	}*/
}