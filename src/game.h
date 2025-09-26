#pragma once

#include "objects/player.h"
#include "objects/ball.h"
#include "scenes/gameUI.h"
#include "objects/brick.h"

namespace crabOut
{
	void GamePlay();
	void Init(Player& player1,Ball& ball, Pong& gameStats, Brick brick[]);
	void Update(Player& player1, Pong& gameStats, Ball& ball, Brick brick[]);
	void Draw(Player player1, Ball& ball, Pong& gameStats, Brick brick[]);
	void DeInit(Pong& gameStats);
}
