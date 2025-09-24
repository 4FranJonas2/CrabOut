#pragma once

#include "objects/player.h"
#include "objects/ball.h"
#include "scenes/gameUI.h"

namespace crabOut
{
	void GamePlay();
	void Init(Player& player1,Ball& ball, Pong& gameStats);
	void Update(Player& player1, Pong& gameStats, Ball& ball);
	void Draw(Player player1, Ball& ball, Pong& gameStats);
}
