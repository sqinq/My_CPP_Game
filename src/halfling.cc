

#include "halfling.h"
#include "floor.h"

// see halfling.h for documentation
Halfling::Halfling(Floor * game) : MoveableEnemy(100, 15, 20)
{
    setGame(game);
    setType("halfling");
    setOverallType("enemy");
}
