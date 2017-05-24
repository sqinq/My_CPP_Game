

#include "elf.h"
#include "floor.h"
#include "playable.h"

// see elf.h for documentation
Elf::Elf(Floor * game) : MoveableEnemy(140, 20, 20)
{
    setGame(game);
    setType("elf");
    setOverallType("enemy");
}

// see elf.h for documentation
void Elf::action()
{
    // we first try to attack
    if (tryToAttack())
    {
        // and then we can attack again if player isn't drow
        if (getGame()->getPlayer()->getType() != "Drow")
        {
            // but we only do so if player still has health
            if (getGame()->getPlayer()->getHp() != 0)
            {
                tryToAttack();
            }
        }
    }
    // otherwise we move
    else
    {
        move();
    }
}
