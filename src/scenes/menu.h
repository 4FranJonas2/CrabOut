#pragma once

#include "sl.h"

#include "..\utilities.h"

#include <string>

using namespace std;

namespace crabOut
{
	struct MenuButtons
	{
		Rectangle backButton;
		Rectangle playButton;
		Rectangle rulesButton;
		Rectangle creditsButton;
		Rectangle linkButton;
	};
	void InitButtons(MenuButtons& buttons);

	void UpdateSceneMenus(GameStats& gamestats, MenuButtons buttons);
	
	void DrawMainMenu(GameStats gameStats, MenuButtons buttons);
	void DrawRulesMenu(GameStats gameStats, MenuButtons buttons);
	void DrawCreditsMenu(GameStats gameStats, MenuButtons buttons);
	void DrawButtonRec(Rectangle button);

	bool IsMouseOverButton(Rectangle buttonRec);
	void PrintMenuText(float posX, float posY, std::string text);
}