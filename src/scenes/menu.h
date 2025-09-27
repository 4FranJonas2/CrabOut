#pragma once

#include "sl.h"

#include "..\utilities.h"

#include <string>

using namespace std;

namespace crabOut
{
	void DrawMainMenu(GameStats gameStats);
	void DrawRulesMenu(GameStats gameStats);
	void PrintMenuText(float posX, float posY, std::string text);

}