#ifndef __DRAGON_H__
#define __DRAGON_H__

#include "enemy.h"

class Floor;

class Dragon : public Enemy
{
public:
	// constructor
    Dragon(Floor * game);

    // action() is called for the object to move one turn
    void action();
};

#endif
