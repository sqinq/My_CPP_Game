#include "dragon.h"
#include "floor.h"

using namespace std;

// see dragon.h for documentation
Dragon::Dragon(Floor * game) : Enemy(150, 20, 20)
{
    setGame(game);
    setType("dragon");
}

// see dragon.h for documentation
void Dragon::action()
{
    tryToAttack();
}
