#pragma once

namespace crabOut
{
	struct Vector2
	{
		float x;
		float y;
	};

	struct Colors
	{
		float r;
		float g;
		float b;
		float a;
	};

	struct Rectangle
	{
		Vector2 recPos;
		Vector2 recSize;
	};

	enum class SceneStatus
	{
		INITGAME = 1,
		GAMEMENU,
		GAMEPLAY,
		GAMEPAUSE,
		RESETGAME,
		GAMEEND,
		SIMEND
	};

	struct Pong
	{
		SceneStatus gameManager;
		const int screenWidth = 750;
		const int screenHeight = 650;
	};
}
