#include "menu.h"


namespace crabOut
{
	Vector2 recSize = { 90.0, 50.0};

	void InitButtons(MenuButtons& buttons)
	{
		buttons.backButton.recPos.x = 80.0;
		buttons.backButton.recPos.y = 45.0;
		buttons.backButton.recSize.x = 100.0;
		buttons.backButton.recSize.y = 50.0;
	}

	void UpdateSceneMenus(GameStats& gamestats, MenuButtons buttons)
	{
		bool enterIsPressed = false;
		bool enterWasPressed = false;

		enterWasPressed = enterIsPressed;
		enterIsPressed = slGetMouseButton(SL_MOUSE_BUTTON_LEFT);

		if (gamestats.gameStatus == SceneStatus::GAMEMENU)
		{
			if (!enterWasPressed && enterIsPressed && IsMouseOverButton(buttons.playButton))
			{
				gamestats.gameStatus = SceneStatus::FIRSTGAME;
			}
			if (!enterWasPressed && enterIsPressed && IsMouseOverButton(buttons.rulesButton))
			{
				gamestats.gameStatus = SceneStatus::GAMERULES;
			}
			if (!enterWasPressed && enterIsPressed && IsMouseOverButton(buttons.creditsButton))
			{
				gamestats.gameStatus = SceneStatus::GAMECREDITS;
			}
		}

		if (gamestats.gameStatus == SceneStatus::GAMERULES)
		{
			if (enterWasPressed && enterIsPressed && IsMouseOverButton(buttons.backButton))
			{
				gamestats.gameStatus = SceneStatus::GAMEMENU;
			}
		}

		if (gamestats.gameStatus == SceneStatus::GAMECREDITS)
		{
			if (enterWasPressed && enterIsPressed && IsMouseOverButton(buttons.linkButton))
			{
				system("start https://4franjonas2.itch.io/");
			}

			if (enterWasPressed && enterIsPressed && IsMouseOverButton(buttons.backButton))
			{
				gamestats.gameStatus = SceneStatus::GAMEMENU;
			}
		}
	}

	void DrawMainMenu(GameStats gameStats, MenuButtons buttons)
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

	void DrawRulesMenu(GameStats gameStats, MenuButtons buttons)
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

			DrawButtonRec(buttons.backButton);
		}

	}

	void DrawCreditsMenu(GameStats gameStats, MenuButtons buttons)
	{
		float lineText1PosX = gameStats.screenWidth / 2 - 50.0;
		float LineText1PosY = 600.0;

		float LineText2PosX = 10.0;
		float LineText2PosY = 480.0;

		/*float LineText3PosX = gameStats.screenWidth / 2 - 150.0;
		float LineText3PosY = 410.0;

		float LineText4PosX = 100.0;
		float LineText4PosY = 330.0;

		float LineText5PosX = 170.0;
		float LineText5PosY = 300.0;*/

		float LineText6PosX = 50.0;
		float LineText6PosY = 35.0;

		if (gameStats.gameStatus == SceneStatus::GAMECREDITS)
		{
			int auxXPos = 15.0;
			int auxFontSize = 15;
			string titleText = "CREDITS";

			string howToMoveText = "-Game made by me Francisco Jonas: https://4franjonas2.itch.io/.";
			/*string winConditionText = "-Break all the blocks to win";
			string loseConditionText1 = "-You will have 3 Lives, if the ball touch the bottom you ";
			string loseConditionText2 = "lose 1 live, lose them all and its game over.";*/
			string exitText = "Back";

			PrintMenuText(lineText1PosX, LineText1PosY, titleText);

			slSetFontSize(15);
			PrintMenuText(LineText2PosX, LineText2PosY, howToMoveText);
			/*PrintMenuText(LineText3PosX, LineText3PosY, winConditionText);
			PrintMenuText(LineText4PosX - auxXPos, LineText4PosY, loseConditionText1);
			PrintMenuText(LineText5PosX - auxXPos, LineText5PosY, loseConditionText2);*/
			slSetFontSize(gameStats.fontSize);
			PrintMenuText(LineText6PosX - auxXPos, LineText6PosY, exitText);

			DrawButtonRec(buttons.backButton);

		}

	}

	void DrawButtonRec(Rectangle button)
	{
		Colors white = { 1.0f,1.0f,1.0f,1.0f };

		slSetForeColor(white.r, white.g, white.b, white.a);

		slRectangleOutline(button.recPos.x, button.recPos.y,
			button.recSize.x, button.recSize.y);
	}

	bool IsMouseOverButton(Rectangle buttonRec)
	{
		int mouseXPos = slGetMouseX();
		int mouseYPos = slGetMouseY();

		float left = buttonRec.recPos.x - buttonRec.recSize.x / 2;
		float right = buttonRec.recPos.x + buttonRec.recSize.x / 2;
		float top = buttonRec.recPos.y - buttonRec.recSize.y / 2;
		float bottom = buttonRec.recPos.y + buttonRec.recSize.y / 2;

		if (mouseXPos >= left && mouseXPos <= right && mouseYPos >= top && mouseYPos <= bottom)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void PrintMenuText(float posX, float posY, string text)
	{
		Colors white = { 1.0f,1.0f,1.0f,1.0f };

		slSetForeColor(white.r, white.g, white.b, white.a);
		slText(posX, posY, text.c_str());
	}
}