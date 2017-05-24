#ifndef __MOVEABLE_ENEMY_H__
#define __MOVEABLE_ENEMY_H__

#include "enemy.h"

class MoveableEnemy : public Enemy
{
public:
	// constructor
    MoveableEnemy(int hp, int attack, int defence);
   
    // action() is called for a single move
    void action();
};

#endif
