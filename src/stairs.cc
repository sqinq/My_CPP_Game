

#include "stairs.h"
#include "floor.h"

#include <string>

using namespace std;

// see stairs.h for documentation
Stairs::Stairs(Floor * game) : Playable(0, 0, 0)
{
	setGame(game);
	setType("stairs");
	setOverallType("stairs");
}

// see stairs.h for documentation
Stairs * Stairs::getStairs(Floor * game)
{
	return new Stairs(game);
}

// see stairs.h for documentation
string Stairs::getType()
{
	return "stairs";
}
