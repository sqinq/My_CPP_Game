

#include "moveableenemy.h"

// see moveableenemy.h for documentation
MoveableEnemy::MoveableEnemy(int hp, int attack, int defence) : Enemy(hp, attack, defence)
{

}

// see moveableenemy.h for documentation
void MoveableEnemy::action()
{
    if (!tryToAttack()) move();
}
