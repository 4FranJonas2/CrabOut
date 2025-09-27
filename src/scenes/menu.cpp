#include "menu.h"


namespace crabOut
{
	Vector2 recSize = { 90.0, 50.0};

	bool IsMouseOverButton(Rectangle buttonRec)
	{
		int mouseXPos = slGetMouseX();
		int mouseYPos = slGetMouseY();

		float left = buttonRec.recPos.x - buttonRec.recSize.x / 2;
		float right = buttonRec.recPos.x + buttonRec.recSize.x / 2;
		float top = buttonRec.recPos.y + buttonRec.recSize.y / 2;
		float bottom = buttonRec.recPos.y - buttonRec.recSize.y / 2;

		if (mouseXPos >= left && mouseXPos <= right && mouseYPos <= top && mouseYPos >= bottom)
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

	void InitButtons(MenuButtons& buttons)
	{
		buttons.backButton.recPos.x = 80.0;
		buttons.backButton.recPos.y = 45.0;
		buttons.backButton.recSize.x = 100.0;
		buttons.backButton.recSize.y = 50.0;

		buttons.linkButton.recPos.x = 575.0;
		buttons.linkButton.recPos.y = 485.0;
		buttons.linkButton.recSize.x = 330.0;
		buttons.linkButton.recSize.y = 30.0;

		buttons.playButton.recPos.x = 395.0;
		buttons.playButton.recPos.y = 390.0;
		buttons.playButton.recSize.x = 100.0;
		buttons.playButton.recSize.y = 40.0;

		buttons.rulesButton.recPos.x = 395.0;
		buttons.rulesButton.recPos.y = 320.0;
		buttons.rulesButton.recSize.x = 130.0;
		buttons.rulesButton.recSize.y = 40.0;

		buttons.creditsButton.recPos.x = 395.0;
		buttons.creditsButton.recPos.y = 260.0;
		buttons.creditsButton.recSize.x = 150.0;
		buttons.creditsButton.recSize.y = 40.0;
	}

	void UpdateSceneMenus(GameStats& gameStats, MenuButtons buttons)
	{	
		gameStats.enterWasPressed = gameStats.enterIsPressed;
		gameStats.enterIsPressed = slGetMouseButton(SL_MOUSE_BUTTON_LEFT);

		if (gameStats.gameStatus == SceneStatus::GAMEMENU)
		{
			if (!gameStats.enterWasPressed && gameStats.enterIsPressed && IsMouseOverButton(buttons.playButton))
			{
				gameStats.gameStatus = SceneStatus::FIRSTGAME;
			}
			else if (!gameStats.enterWasPressed && gameStats.enterIsPressed && IsMouseOverButton(buttons.rulesButton))
			{
				gameStats.gameStatus = SceneStatus::GAMERULES;
			}
			else if (!gameStats.enterWasPressed && gameStats.enterIsPressed && IsMouseOverButton(buttons.creditsButton))
			{
				gameStats.gameStatus = SceneStatus::GAMECREDITS;
			}
		}

		else if (gameStats.gameStatus == SceneStatus::GAMERULES)
		{
			if (!gameStats.enterWasPressed && gameStats.enterIsPressed && IsMouseOverButton(buttons.backButton))
			{
				gameStats.gameStatus = SceneStatus::GAMEMENU;
			}
		}

		else if (gameStats.gameStatus == SceneStatus::GAMECREDITS)
		{
			if (!gameStats.enterWasPressed && gameStats.enterIsPressed && IsMouseOverButton(buttons.linkButton))
			{
				system("start https://4franjonas2.itch.io/");
			}

			else if (!gameStats.enterWasPressed && gameStats.enterIsPressed && IsMouseOverButton(buttons.backButton))
			{
				gameStats.gameStatus = SceneStatus::GAMEMENU;
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
			string exitText = "Press ESC at ANY momment to CLOSE the game";

			PrintMenuText(lineText1PosX, LineText1PosY, titleText);
			PrintMenuText(LineText2PosX, LineText2PosY, playText);
			PrintMenuText(LineText3PosX, LineText3PosY, rulesext);
			PrintMenuText(LineText4PosX - auxXPos, LineText4PosY, creditsText);
			
			slSetFontSize(10);
			PrintMenuText(LineText5PosX - auxXPos, LineText5PosY, exitText);
			slSetFontSize(gameStats.fontSize);

			DrawButtonRec(buttons.playButton);
			DrawButtonRec(buttons.rulesButton);
			DrawButtonRec(buttons.creditsButton);
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

			DrawButtonRec(buttons.linkButton);
			DrawButtonRec(buttons.backButton);

		}

	}

	void DrawPause(GameStats gameStats)
	{
		if (gameStats.gameStatus == SceneStatus::GAMEPAUSE || gameStats.gameStatus == SceneStatus::FIRSTGAME)
		{
			float lineText1PosX = gameStats.screenWidth / 2 - 90.0;
			float LineText1PosY = 400.0;

			float LineText2PosX = gameStats.screenWidth / 2 - 135.0;
			float LineText2PosY = 310.0;

			float LineText3PosX = gameStats.screenWidth / 2 - 100.0;
			float LineText3PosY = 270.0;

			float LineText4PosX = 190;
			float LineText4PosY = 220.0;

			float LineText5PosX = 160;
			float LineText5PosY = 170.0;

			string pauseText = "GAME PAUSE";
			string keyInstructionText = "Press ENTER key";
			string continueText = "To Continue";
			string startText = "To Start Game";
			string resetText = "Press R to reset game";
			string menuText = "Press M to go to the MENU";

			PrintMenuText(lineText1PosX, LineText1PosY, pauseText);
			PrintMenuText(LineText2PosX, LineText2PosY, keyInstructionText);

			if (gameStats.gameStatus == SceneStatus::GAMEPAUSE)
			{
				PrintMenuText(LineText3PosX, LineText3PosY, continueText);
				PrintMenuText(LineText4PosX, LineText4PosY, resetText);
				PrintMenuText(LineText5PosX, LineText5PosY, menuText);
			}
			if (gameStats.gameStatus == SceneStatus::FIRSTGAME)
			{
				int auxXPos = 15.0;
				PrintMenuText(LineText3PosX - auxXPos, LineText3PosY, startText);
				PrintMenuText(LineText5PosX, LineText5PosY, menuText);
			}
		}

		if (gameStats.gameStatus == SceneStatus::GAMEEND)
		{
			float lineText1PosX = gameStats.screenWidth / 2 - 90.0;
			float LineText1PosY = 400.0;

			float LineText2PosX = gameStats.screenWidth / 2 - 225.0;
			float LineText2PosY = 310.0;

			float LineText3PosX = gameStats.screenWidth / 2 - 210.0;
			float LineText3PosY = 270.0;

			string endText = "GAME ENDED";
			string keyInstructionText = "Press ENTER to RESTART";
			string restartText = "or M to go to the MENU";

			PrintMenuText(lineText1PosX, LineText1PosY, endText);
			PrintMenuText(LineText2PosX, LineText2PosY, keyInstructionText);
			PrintMenuText(LineText3PosX, LineText3PosY, restartText);
		}

	}

	void DrawButtonRec(Rectangle button)
	{
		Colors white = { 1.0f,1.0f,1.0f,1.0f };

		slSetForeColor(white.r, white.g, white.b, white.a);

		slRectangleOutline(button.recPos.x, button.recPos.y,
			button.recSize.x, button.recSize.y);
	}
}