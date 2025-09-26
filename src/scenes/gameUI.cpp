#include "gameUI.h"
//iankuz
using namespace std;

namespace crabOut
{
	Colors white = { 1.0f,1.0f,1.0f,1.0f };

	void PrintScore(int playerScore, GameStats gameStats)
	{
		float textPosX = 15.0;
		float textPosY = gameStats.screenHeight - 30.0;
		string scoreText = "Score: " + to_string(playerScore);
		PrintText(textPosX, textPosY, scoreText);
	}

	void PrintLives(int playerLives, GameStats gameStats)
	{
		float textPosX = gameStats.screenWidth - 160.0;
		float textPosY = gameStats.screenHeight - 30.0;
		string livesText = "Lives: " + to_string(playerLives);
		PrintText(textPosX, textPosY, livesText);
	}

	void PrintPause(GameStats gameStats)
	{
		float lineText1PosX = gameStats.screenWidth / 2 - 30.0;
		float LineText1PosY = 200.0;

		float LineText2PosX = gameStats.screenWidth / 2 - 30.0;
		float LineText2PosY = 220.0;

		float LineText3PosX = gameStats.screenWidth / 2 - 30.0;
		float LineText3PosY = 240.0;

		string pauseText = "GAME PAUSE";
		string keyInstructionText = "Press ENTER key";
		string continueText = "To Continue";

		PrintText(lineText1PosX, LineText1PosY, pauseText);
		PrintText(lineText1PosX, LineText1PosY, keyInstructionText);
		PrintText(lineText1PosX, LineText1PosY, continueText);
	}

	void PrintText(float posX, float posY, string text)
	{
		slSetForeColor(white.r, white.g, white.b, white.a);
		slText(posX, posY, text.c_str());
	}

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