#pragma once

#include "objects/player.h"
#include "objects/ball.h"
#include "scenes/gameUI.h"

namespace pong2
{
	void GamePlay();
	void Init(Player& player1, Player& player2,Ball& ball, Pong& gameStats);
	void Update(Player& player1, Player& player2, Pong& gameStats, Ball& ball);
	void Draw(Player player1, Player player2, Ball& ball, Pong& gameStats);
}
