#include "menu.h"


namespace crabOut
{
	void DrawMainMenu(GameStats gameStats)
	{
		float lineText1PosX = gameStats.screenWidth / 2 - 50.0;
		float LineText1PosY = 500.0;

		float LineText2PosX = gameStats.screenWidth / 2 - 20.0;
		float LineText2PosY = 380.0;

		float LineText3PosX = gameStats.screenWidth / 2 - 30.0;
		float LineText3PosY = 310.0;

		float LineText4PosX = gameStats.screenWidth / 2 - 35.0;
		float LineText4PosY = 250.0;

		float LineText5PosX = 250.0;
		float LineText5PosY = 5.0;

		if (gameStats.gameStatus == SceneStatus::GAMEMENU)
		{
			int auxXPos = 15.0;
			string titleText = "CRABOUT";
			string playText = "Play";
			string rulesext = "Rules";
			string creditsText = "Credits";
			string exitText = "Press ESC at ANY momment to close the game";

			PrintMenuText(lineText1PosX, LineText1PosY, titleText);
			PrintMenuText(LineText2PosX, LineText2PosY, playText);
			PrintMenuText(LineText3PosX, LineText3PosY, rulesext);
			PrintMenuText(LineText4PosX - auxXPos, LineText4PosY, creditsText);
			
			slSetFontSize(10);
			PrintMenuText(LineText5PosX - auxXPos, LineText5PosY, exitText);
			slSetFontSize(gameStats.fontSize);
		}

	}

	void DrawRulesMenu(GameStats gameStats)
	{
		float lineText1PosX = gameStats.screenWidth / 2 - 50.0;
		float LineText1PosY = 600.0;

		float LineText2PosX = 100.0;
		float LineText2PosY = 480.0;

		float LineText3PosX = gameStats.screenWidth / 2 - 150.0;
		float LineText3PosY = 410.0;

		float LineText4PosX = 100.0;
		float LineText4PosY = 330.0;

		float LineText5PosX = 170.0;
		float LineText5PosY = 300.0;

		float LineText6PosX = 50.0;
		float LineText6PosY = 35.0;

		if (gameStats.gameStatus == SceneStatus::GAMERULES)
		{
			int auxXPos = 15.0;
			int auxFontSize = 15;
			string titleText = "RULES";
			string howToMoveText = "-To move use A and D keys to move player horizontal.";
			string winConditionText = "-Break all the blocks to win";
			string loseConditionText1 = "-You will have 3 Lives, if the ball touch the bottom you ";
			string loseConditionText2 = "lose 1 live, lose them all and its game over.";
			string exitText = "Back";

			PrintMenuText(lineText1PosX, LineText1PosY, titleText);

			slSetFontSize(15);
			PrintMenuText(LineText2PosX, LineText2PosY, howToMoveText);
			PrintMenuText(LineText3PosX, LineText3PosY, winConditionText);
			PrintMenuText(LineText4PosX - auxXPos, LineText4PosY, loseConditionText1);
			PrintMenuText(LineText5PosX - auxXPos, LineText5PosY, loseConditionText2);
			slSetFontSize(gameStats.fontSize);
			PrintMenuText(LineText6PosX - auxXPos, LineText6PosY, exitText);
		}

	}

	void DrawCreditsMenu(GameStats gameStats)
	{
		float lineText1PosX = gameStats.screenWidth / 2 - 50.0;
		float LineText1PosY = 600.0;

		float LineText2PosX = 100.0;
		float LineText2PosY = 480.0;

		float LineText3PosX = gameStats.screenWidth / 2 - 150.0;
		float LineText3PosY = 410.0;

		float LineText4PosX = 100.0;
		float LineText4PosY = 330.0;

		float LineText5PosX = 170.0;
		float LineText5PosY = 300.0;

		float LineText6PosX = 50.0;
		float LineText6PosY = 35.0;

		if (gameStats.gameStatus == SceneStatus::GAMERULES)
		{
			int auxXPos = 15.0;
			int auxFontSize = 15;
			string titleText = "RULES";
			string howToMoveText = "-To move use A and D keys to move player horizontal.";
			string winConditionText = "-Break all the blocks to win";
			string loseConditionText1 = "-You will have 3 Lives, if the ball touch the bottom you ";
			string loseConditionText2 = "lose 1 live, lose them all and its game over.";
			string exitText = "Back";

			PrintMenuText(lineText1PosX, LineText1PosY, titleText);

			slSetFontSize(15);
			PrintMenuText(LineText2PosX, LineText2PosY, howToMoveText);
			PrintMenuText(LineText3PosX, LineText3PosY, winConditionText);
			PrintMenuText(LineText4PosX - auxXPos, LineText4PosY, loseConditionText1);
			PrintMenuText(LineText5PosX - auxXPos, LineText5PosY, loseConditionText2);
			slSetFontSize(gameStats.fontSize);
			PrintMenuText(LineText6PosX - auxXPos, LineText6PosY, exitText);
		}

	}

	void PrintMenuText(float posX, float posY, string text)
	{
		Colors white = { 1.0f,1.0f,1.0f,1.0f };

		slSetForeColor(white.r, white.g, white.b, white.a);
		slText(posX, posY, text.c_str());
	}

}