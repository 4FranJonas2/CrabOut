#include "../utilities.h"

#include "sl.h"

namespace crabOut
{
	struct PowerUp
	{
		Vector2 powerPos;
		Colors powerColor;
		int powerRad;
		int powerSpeed;
		bool isActive;
		bool isRedPower;
		bool isYellowPower;
		bool isGreenPower;

	};

	void CreatePowerUp(PowerUp& powers, Rectangle brick);

	void UpdatePowerUp(PowerUp& powers, Rectangle& playerRec);

	bool CheckCollisionPowerPlayer(PowerUp& powers, Rectangle playerRec);

}