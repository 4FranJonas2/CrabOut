#include "gameUI.h"
//iankuz
using namespace std;

namespace crabOut
{
	Colors black = { 0.0f,0.0f,0.0f,1.0f };

	void gamePlayUi(int playerLives, int playerScore, GameStats gameStats)
	{
		float livesTextPosX = gameStats.screenWidth - 160.0;
		float livesTextPosY = gameStats.screenHeight - 30.0;
		float scoreTextPosX = 15.0;
		float scoreTextPosY = gameStats.screenHeight - 30.0;
		float pauseTextPosX = 240.0;
		float pauseTextPosY = gameStats.screenHeight - 20.0;

		string livesText = "Lives: " + to_string(playerLives);
		string scoreText = "Score: " + to_string(playerScore);
		string pauseKeyText = "Press ENTER to PAUSE game";

		slSetFontSize(15);
		PrintText(pauseTextPosX, pauseTextPosY, pauseKeyText);
		slSetFontSize(gameStats.fontSize);

		PrintText(livesTextPosX, livesTextPosY, livesText);
		PrintText(scoreTextPosX, scoreTextPosY, scoreText);
	}

	void PrintText(float posX, float posY, string text)
	{
		slSetForeColor(black.r, black.g, black.b, black.a);
		slText(posX, posY, text.c_str());
	}
}