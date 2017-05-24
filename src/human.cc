

#include "human.h"
#include "floor.h"

// see human.h for documentation
Human::Human(Floor * game) : MoveableEnemy(140, 20, 20)
{
    setGame(game);
    setType("human");
    setOverallType("enemy");
}
