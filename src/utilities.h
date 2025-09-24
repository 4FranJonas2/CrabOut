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
		GAMEPLAYTWOPLAYERS,
		GAMEPAUSE,
		RESETGAME,
		GAMEEND
	};

	struct Pong
	{
		SceneStatus gameManager;
		const int screenWidth = 800;
		const int screenHeight = 450;
	};
}
