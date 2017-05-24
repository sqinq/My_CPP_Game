

#include "dwarf.h"
#include "floor.h"

// see dwarf.h for documentation
Dwarf::Dwarf(Floor * game) : MoveableEnemy(100, 20, 30)
{
    setGame(game);
    setType("dwarf");
    setOverallType("enemy");
}
