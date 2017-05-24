

#include "orc.h"
#include "floor.h"

// see orc.h for documentation
Orc::Orc(Floor * game) : MoveableEnemy(180, 30, 25)
{
    setGame(game);
    setType("orc");
}

// see orc.h for documentation
void Orc::action()
{
    if (! tryToAttack()) move();
}
